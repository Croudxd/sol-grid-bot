#include <deque>
class Config
{
    private:
        const char* private_key;
        const char* public_key;
    public:
        static const char* deque_to_const_char(std::deque<char> deque);
        void set_private_key(const char* key);
        void set_public_key(const char* key);
};
