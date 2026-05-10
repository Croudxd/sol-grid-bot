
#include <cstdint>
class Market
{
    private:
        int64_t open_24h;
        int64_t low_24h;
        int64_t volume_24h;
        int64_t volume_30d;
        int64_t best_bid;
        int64_t best_bid_size;
        int64_t best_ask;
        int64_t best_ask_size;

    public:
        Market(
        int64_t _open_24h,
        int64_t _low_24h,
        int64_t _volume_24h,
        int64_t _volume_30d,
        int64_t _best_bid,
        int64_t _best_bid_size,
        int64_t _best_ask,
        int64_t _best_ask_size
        ) :
            open_24h(_open_24h), 
            low_24h(_low_24h), 
            volume_24h(_volume_24h), 
            volume_30d(_volume_30d), 
            best_bid(_best_bid), 
            best_bid_size(_best_bid_size), 
            best_ask(_best_ask), 
            best_ask_size(_best_ask_size) 
    {}
};
