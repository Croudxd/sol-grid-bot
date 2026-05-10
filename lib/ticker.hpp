#pragma once
#include <cstdint>

class Ticker 
{
    private:
        int64_t price;
        int64_t best_bid;
        int64_t best_ask;
        int64_t best_bid_size;
        int64_t best_ask_size;
        int64_t volume_24h;

    public:
        Ticker() : price(0), best_bid(0), best_ask(0), best_bid_size(0), best_ask_size(0), volume_24h(0) {}
        Ticker(
        int64_t _price,
        int64_t _best_bid,
        int64_t _best_bid_size,
        int64_t _best_ask,
        int64_t _best_ask_size,
        int64_t _volume_24h
        ) :
            price(_price), 
            best_bid(_best_bid), 
            best_ask(_best_ask), 
            best_bid_size(_best_bid_size), 
            best_ask_size(_best_ask_size),
            volume_24h(_volume_24h)
    {}
};
