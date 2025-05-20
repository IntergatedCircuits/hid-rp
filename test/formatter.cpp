#include "hid/rdf/formatter.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace hid::page;
using namespace hid::rdf;

TEST_CASE("usage concept type formatter")
{
    auto out = std::format("{:p}", consumer::HELP);
    CHECK(out == "Consumer / Help");

    out = std::format("{}", consumer::HELP);
    CHECK(out == "Help");

    out = std::format("{:p#06x}", (consumer)0xfffe);
    CHECK(out == "Consumer / 0xfffe");

    out = std::format("{:#06x}", (consumer)0xfffe);
    CHECK(out == "0xfffe");

    out = std::format("{}", button(4));
    CHECK(out == "Button 4");

    out = std::format("{:p}", button(4));
    CHECK(out == "Button / Button 4");

    out = std::format("{:p#06x}", ordinal(16));
    CHECK(out == "Ordinal / Instance 16");

    out = std::format("{}", sensor::ELECTRICAL_CURRENT | sensor::MAXIMUM);
    CHECK(out == "Electrical: Current Maximum");
}

TEST_CASE("usage value formatter")
{
    auto out = std::format("{:p}", hid::usage_t(consumer::HELP));
    CHECK(out == "Consumer / Help");

    out = std::format("{}", hid::usage_t(consumer::HELP));
    CHECK(out == "Help");

    out = std::format("{:p#06x}", hid::usage_t((consumer)0xfffe));
    CHECK(out == "Consumer / 0xfffe");

    out = std::format("{:#06x}", hid::usage_t((consumer)0xfffe));
    CHECK(out == "0xfffe");

    out = std::format("{}", hid::usage_t(button(4)));
    CHECK(out == "Button 4");

    out = std::format("{:p}", hid::usage_t(button(4)));
    CHECK(out == "Button / Button 4");

    out = std::format("{:p#06x}", hid::usage_t(ordinal(16)));
    CHECK(out == "Ordinal / Instance 16");

    out = std::format("{:p#06x}", hid::usage_t(0xfedc, 0x1234));
    CHECK(out == "unknown(0xfedc) / 0x1234");

    out = std::format("{}", hid::usage_t(sensor::ELECTRICAL_CURRENT | sensor::MAXIMUM));
    CHECK(out == "Electrical: Current Maximum");
}
