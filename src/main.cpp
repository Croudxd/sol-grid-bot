/**
 * ATR Grid bot for trading SOL on Jupiter
 */
#include <wallet.hpp>
#include <logger.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "bot [key_path] [log_path]" << std::endl;
    }

    std::cout << argv[2];

    Logger::init(argv[2]);
    Wallet wallet = Wallet();
    wallet.LoadKeys(argv[1]);
    return 1;
}
