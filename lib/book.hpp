#pragma once
#include <cstdint>
#include <map>


class Book
{
    private:
        std::map<int64_t, int64_t> asks;
        std::map<int64_t, int64_t, std::greater<int64_t>> bids;
    public:
        void update(int64_t price, int64_t size, bool side);

};
