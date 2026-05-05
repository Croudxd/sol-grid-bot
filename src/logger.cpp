#include <logger.hpp>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <unistd.h>

int Logger::fd = -1;

int Logger::init(const char *path)
{
    time_t current_time = time(nullptr);
    struct tm* tm_info = localtime(&current_time);
    
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d_%H-%M-%S", tm_info);
    
    char nm[128];
    snprintf(nm, sizeof(nm), "%s/%s.log", path, time_str);
    std::cout << nm;
    
    fd = open(nm, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if(fd == -1)
    {
        std::cout << "Error: Failed to open Logger file" << std::endl;
        return -1;
    }
    return 0;
}

int Logger::log(const char* message)
{
    if(write(fd, message, strlen(message)) != strlen(message))
    {
        std::cout << "Error: Failed to write to log file." << std::endl;
        return -1;
    }
    return 0;
}

void Logger::close()
{
    ::close(fd);
}
