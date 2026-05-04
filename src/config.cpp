#include "config.hpp"
#include <deque>

const char* Config::deque_to_const_char(std::deque<char> deque)
{
    char* buf = new char[deque.size() + 1];

    for (size_t i = 0; i < deque.size(); ++i) 
    {
        buf[i] = deque[i];
    }
    buf[deque.size()] = '\0';

    const char* ptr = buf;

    delete[] buf; 
    return ptr;
}


void Config::set_private_key(const char* key)
{
    this->private_key = key;
}

void Config::set_public_key(const char* key)
{
    this->public_key = key;
}
