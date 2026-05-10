#include <cstdint>
#include <cstring>
#include <string_view>
#include <websockets.hpp>
#include <arpa/inet.h> // inet_addr()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <simdjson.h>
#include <book.hpp>
#include <json.hpp>

#define PORT "443"
#define ADDR "advanced-trade-ws.coinbase.com"

int Websocket::tcp_connect()
{
       SSL_library_init();
       SSL_load_error_strings();
       ctx = SSL_CTX_new(TLS_client_method());

       if (ctx == nullptr)
       {
           // TODO: Log
       }

       struct addrinfo  hints{};
       struct addrinfo  *result{};

       hints.ai_socktype = SOCK_STREAM; 
       int rs = getaddrinfo(ADDR, PORT, &hints, &result);
       if (rs < 0)
       {
           //TODO: Log error
           return -1;
       }

       tcpfd = socket(result->ai_family, result->ai_socktype, 0);
       int c = connect(tcpfd, result->ai_addr, result->ai_addrlen);

       ssl = SSL_new(ctx);
       SSL_set_fd(ssl, tcpfd);
       SSL_set_tlsext_host_name(ssl, ADDR);
       if(SSL_connect(ssl) <= 0)
       {
            // TODO: log error
            return -1;
       }
       return 0;
}

int Websocket::handshake()
{
       char message[512];
       snprintf(message, sizeof(message),
           "GET / HTTP/1.1\r\n"
           "Host: advanced-trade-ws.coinbase.com\r\n"
           "Upgrade: websocket\r\n"
           "Connection: Upgrade\r\n"
           "Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==\r\n"
           "Sec-WebSocket-Version: 13\r\n\r\n");

       SSL_write(ssl, message, strlen(message));
       char response[4096];
       int bytes = SSL_read(ssl, response, sizeof(response));
       return 0;
}

int Websocket::subscribe()
{
       const char* subscribe_ticker = "{\"type\":\"subscribe\",\"product_ids\":[\"BTC-USD\"],\"channel\":\"ticker\"}";
       const char* subscribe_l2 = "{\"type\":\"subscribe\",\"product_ids\":[\"BTC-USD\"],\"channel\":\"level2\"}";
       send_frame(subscribe_ticker);
       send_frame(subscribe_l2);
       return 0;
}

int Websocket::run()
{
       simdjson::ondemand::parser parser;
       while(true)
       {
           uint8_t header[2];
           SSL_read(ssl, header, 2);
           
           size_t len = header[1] & 0x7F;
           
           if(len == 126)
           {
               uint8_t ext[2];
               SSL_read(ssl, ext, 2);
               len = (ext[0] << 8) | ext[1];
           }
           else if(len == 127)
           {
               uint8_t ext[8];
               SSL_read(ssl, ext, 8);
               len = 0;
               for(int i = 0; i < 8; i++)
                   len = (len << 8) | ext[i];
           }

           std::vector<char> buffer(len + simdjson::SIMDJSON_PADDING);
           size_t total = 0;
           while(total < len)
           {
               int bytes = SSL_read(ssl, buffer.data() + total, len - total);
               if(bytes <= 0) break;
               total += bytes;
           }

           simdjson::padded_string json(buffer.data(), len);
           auto doc = parser.iterate(json);
           std::string_view channel = doc["channel"].get_string().value();
           if(channel == "l2_data")
           {
               for(auto event : doc["events"])
                   for(auto update : event["updates"])
                       Json::updates_to_book(book, update);
           }
           else if(channel == "ticker")
           {
               for(auto event : doc["events"])
                   for(auto ticker : event["tickers"])
                       Json::ticker_to_trade(market, ticker);
           }
        }
}

void Websocket::send_frame(const char* payload)
{
    size_t len = strlen(payload);

    uint8_t key[4];
    RAND_bytes(key, 4);

    uint8_t header[6];
    header[0] = 0x81;
    header[1] = 0x80 | len;
    header[2] = key[0];
    header[3] = key[1];
    header[4] = key[2];
    header[5] = key[3];

    uint8_t masked[len];
    for (size_t i = 0; i < len; i++)
        masked[i] = payload[i] ^ key[i % 4];

    SSL_write(ssl, header, 6);
    SSL_write(ssl, masked, len);
}
