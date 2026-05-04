/**
 * ATR Grid bot for trading SOL on Jupiter
 */
#include "wallet.hpp"



static const char *path = "/home/ben/dev/sol-grid-bot/.env";


int main()
{
    Wallet wal = Wallet();
    wal.LoadKeys(path);
    return 1;
}
