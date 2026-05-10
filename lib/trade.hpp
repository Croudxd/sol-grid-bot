
#include <cstdint>

class Trade 
{
    private:
        int64_t price;
        bool side;
        int64_t size;
        int64_t time;
    public:
        Trade(int64_t _price, bool _side, int64_t _size, int64_t _time) : price(_price), side(_side), size(_size), time(_time) {}
};
