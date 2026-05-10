#pragma once
#include <openssl/ssl.h>
#include <book.hpp>
#include <market.hpp>

class Websocket
{
    private:
        int tcpfd;
        SSL *ssl;
        SSL_CTX *ctx;
        Market& market;
        Book& book;
    public:
        Websocket(Market& _market, Book& _book) : market(_market), book(_book) {}
        int tcp_connect();
        int handshake();
        int subscribe();
        int run();
        void send_frame(const char* payload);
};
