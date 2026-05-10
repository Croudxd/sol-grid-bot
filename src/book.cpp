#include <book.hpp>
#include <cstdint>

void Book::update(int64_t price, int64_t size, bool is_bid)
{
    if(is_bid)
        size == 0 ? bids.erase(price) : bids[price] = size;
    else
        size == 0 ? asks.erase(price) : asks[price] = size;
}
