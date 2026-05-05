cmake_minimum_required(VERSION 3.23)

project(sol-grid-bot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(
    SOURCES 
        src/main.cpp
        src/wallet.cpp
        src/logger.cpp
        src/config.cpp
)

add_executable(bot ${SOURCES})

target_compile_options(bot PRIVATE 
    -g          # debug symbols
    -Wall       # all warnings
    -Wextra     # extra warnings
    -O0         # no optimisation (easier to debug)
)

target_include_directories(bot
    PUBLIC 
        include 
        lib
)
