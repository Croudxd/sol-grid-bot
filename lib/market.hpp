#pragma once
#include <cstddef>
#include <ticker.hpp>

class Market
{
    private:
        static constexpr size_t MAX_TICKS = 1000;
        Ticker ticks[MAX_TICKS];
        size_t head = 0;
    public:
        Market();
        void add(Ticker t);
        Ticker& latest();
};
