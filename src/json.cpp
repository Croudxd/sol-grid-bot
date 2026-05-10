#include <json.hpp>
#include <simdjson.h>
#include <string_view>
#include <string>

void Json::updates_to_book(Book &book, simdjson::simdjson_result<simdjson::ondemand::value> update)
{
    std::string_view side = update["side"].get_string().value();
    std::string_view price = update["price_level"].get_string().value();
    std::string_view qty = update["new_quantity"].get_string().value();

    double _price = std::stod(std::string(price));
    int64_t price_int = static_cast<int64_t>(_price * 100);

    bool is_bid = (side == "bid");

    double _qty = std::stod(std::string(qty));
    int64_t qty_int = static_cast<int64_t>(_price * 100'000'000);

    book.update(price_int, qty_int, is_bid);
}

void Json::ticker_to_trade(Market &market, simdjson::simdjson_result<simdjson::ondemand::value> ticker)
{
    std::string_view price = ticker["price"].get_string().value();
    std::string_view best_bid = ticker["best_bid"].get_string().value();
    std::string_view best_ask = ticker["best_ask"].get_string().value();
    std::string_view best_bid_qty = ticker["best_bid_quantity"].get_string().value();
    std::string_view best_ask_qty = ticker["best_ask_quantity"].get_string().value();
    std::string_view volume_24h = ticker["volume_24_h"].get_string().value();

    double _price = std::stod(std::string(price));
    int64_t price_int = static_cast<int64_t>(_price * 100);

    double _best_bid = std::stod(std::string(best_bid));
    int64_t best_bid_int = static_cast<int64_t>(_best_bid * 100);

    double _best_ask = std::stod(std::string(best_ask));
    int64_t best_ask_int = static_cast<int64_t>(_best_ask * 100);

    double _best_bid_qty = std::stod(std::string(best_bid_qty));
    int64_t best_bid_qty_int = static_cast<int64_t>(_best_bid_qty * 100'000'000);

    double _best_ask_qty = std::stod(std::string(best_ask_qty));
    int64_t best_ask_qty_int = static_cast<int64_t>(_best_ask_qty * 100'000'000);

    double _vol = std::stod(std::string(volume_24h));
    int64_t vol_int = static_cast<int64_t>(_vol * 100'000'000);

    Ticker t = Ticker(price_int, best_bid_int, best_ask_int, best_bid_qty_int, best_ask_qty_int, vol_int);
    market.add(t);
}
