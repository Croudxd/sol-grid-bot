cmake_minimum_required(VERSION 3.23)

project(sol-grid-bot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)
include(FetchContent)

FetchContent_Declare(
    simdjson
    GIT_REPOSITORY https://github.com/simdjson/simdjson.git
    GIT_TAG v4.6.4 
)

FetchContent_MakeAvailable(simdjson)

set(
    SOURCES 
        src/main.cpp
        src/wallet.cpp
        src/logger.cpp
        src/config.cpp
        src/websocket.cpp
        src/market.cpp
        src/json.cpp
        src/book.cpp
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

target_link_libraries(bot PRIVATE OpenSSL::SSL OpenSSL::Crypto simdjson::simdjson)
