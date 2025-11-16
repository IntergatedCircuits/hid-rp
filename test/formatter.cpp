#include "hid/rdf/formatter.hpp"
#include "test_framework.hpp"
#include <string_view>
using namespace std::literals::string_view_literals;

using namespace hid::page;
using namespace hid::rdf;

SUITE(formatter)
{
    TEST_CASE("formatter - usage concept type")
    {
        auto out = std::format("{:p}", consumer::HELP);
        CHECK(out == "Consumer / Help"sv);

        out = std::format("{}", consumer::HELP);
        CHECK(out == "Help"sv);

        out = std::format("{:p#06x}", (consumer)0xfffe);
        CHECK(out == "Consumer / 0xfffe"sv);

        out = std::format("{:#06x}", (consumer)0xfffe);
        CHECK(out == "0xfffe"sv);

        out = std::format("{}", button(4));
        CHECK(out == "Button 4"sv);

        out = std::format("{:p}", button(4));
        CHECK(out == "Button / Button 4"sv);

        out = std::format("{:p#06x}", ordinal(16));
        CHECK(out == "Ordinal / Instance 16"sv);

        out = std::format("{}", sensor::ELECTRICAL_CURRENT | sensor::MAXIMUM);
        CHECK(out == "Electrical: Current Maximum"sv);
    };

    TEST_CASE("formatter - usage value")
    {
        auto out = std::format("{:p}", hid::usage_t(consumer::HELP));
        CHECK(out == "Consumer / Help"sv);

        out = std::format("{}", hid::usage_t(consumer::HELP));
        CHECK(out == "Help"sv);

        out = std::format("{:p#06x}", hid::usage_t((consumer)0xfffe));
        CHECK(out == "Consumer / 0xfffe"sv);

        out = std::format("{:#06x}", hid::usage_t((consumer)0xfffe));
        CHECK(out == "0xfffe"sv);

        out = std::format("{}", hid::usage_t(button(4)));
        CHECK(out == "Button 4"sv);

        out = std::format("{:p}", hid::usage_t(button(4)));
        CHECK(out == "Button / Button 4"sv);

        out = std::format("{:p#06x}", hid::usage_t(ordinal(16)));
        CHECK(out == "Ordinal / Instance 16"sv);

        out = std::format("{:p#06x}", hid::usage_t(0xfedc, 0x1234));
        CHECK(out == "unknown(0xfedc) / 0x1234"sv);

        out = std::format("{}", hid::usage_t(sensor::ELECTRICAL_CURRENT | sensor::MAXIMUM));
        CHECK(out == "Electrical: Current Maximum"sv);
    };
};
