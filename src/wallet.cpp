#include <cstring>
#include <wallet.hpp>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <deque>
#include <logger.hpp>

Wallet::Wallet() 
{

}

Config Wallet::LoadKeys(const char *path)
{
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    int fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        Logger::log("ERROR: Failed to open keys");
    }
    read(fd, buf, sizeof(buf));

    std::deque<char> line_one;
    std::deque<char> line_two;

    int buf_size = sizeof(buf) / sizeof(buf[0]);
    int one_start = 0;
    int two_start = 0;

    bool found = false;
    for (size_t i = {}; i < buf_size; i++)
    {
        if(buf[i] == '\000') break;
        if(buf[i] == '\n') 
        {
            found = true;
            continue;
        }

        if (buf[i] == '=')
        {
            if ( found == false  ) one_start = i+1;

            else two_start = line_two.size() + 1;
        }
        if (found == true)
        {
            line_two.push_back(buf[i]);
        }
        else if (found == false)
        {
            line_one.push_back(buf[i]);
        }
    }

    for (size_t i = {}; i < one_start; i++)
    {
        if (line_one.size() != 0)
        {
            line_one.pop_front();
        }
    }

    for (size_t i = {}; i < two_start; i++)
    {
        if (line_two.size() != 0)
        {
            line_two.pop_front();
        }
    }

    Config cfg = Config();
    cfg.set_private_key(Config::deque_to_const_char(line_one));
    cfg.set_public_key(Config::deque_to_const_char(line_two));

    close(fd);
    return cfg;
}
