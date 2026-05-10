#pragma once
#include <book.hpp>
#include <simdjson.h>
#include <market.hpp>

class Json
{
    private:
    public:
        Json();
        static void updates_to_book(Book &book, simdjson::simdjson_result<simdjson::ondemand::value> update);
        static void ticker_to_trade(Market& market, simdjson::simdjson_result<simdjson::ondemand::value> ticker);

};
