#include <market.hpp>

Market::Market() 
{

}
void Market::add(Ticker t)
{
    ticks[head % MAX_TICKS] = t;
}

Ticker& Market::latest()
{
    return ticks[(head - 1) % MAX_TICKS];
}
