#include <cstdint>
#include <map>


class Book
{
    private:
        std::map<int64_t, int64_t> asks;
        std::map<int64_t, int64_t, std::greater<int64_t>> bids;
    public:
        void add(int64_t price, int64_t size, bool side);
        void remove(int64_t price, bool side);

};
