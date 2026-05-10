#include <openssl/ssl.h>

class Websocket
{
    private:
    public:
        Websocket();
        void sendFrame(SSL* ssl, const char* payload);
};
