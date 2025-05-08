#include "hid/rdf/descriptor_view.hpp"
#include "hid/rdf/descriptor.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace hid::rdf;

TEST_CASE("has valid bounds")
{
    constexpr auto a0_0 = std::to_array<std::uint8_t>({0x00});
    static_assert(ce_descriptor_view(a0_0).begin()->data_size() == 0);
    static_assert(ce_descriptor_view(a0_0).has_valid_bounds());
    CHECK(descriptor_view(a0_0).begin()->data_size() == 0);
    CHECK(descriptor_view(a0_0).has_valid_bounds());

    constexpr auto a1_1 = std::to_array<std::uint8_t>({0x01, 42});
    static_assert(ce_descriptor_view(a1_1).begin()->data_size() == 1);
    static_assert(ce_descriptor_view(a1_1).has_valid_bounds());
    CHECK(descriptor_view(a1_1).begin()->data_size() == 1);
    CHECK(descriptor_view(a1_1).has_valid_bounds());

    constexpr auto a2_2 = std::to_array<std::uint8_t>({0x02, 0xa, 0xb});
    static_assert(ce_descriptor_view(a2_2).begin()->data_size() == 2);
    static_assert(ce_descriptor_view(a2_2).has_valid_bounds());
    CHECK(descriptor_view(a2_2).begin()->data_size() == 2);
    CHECK(descriptor_view(a2_2).has_valid_bounds());

    constexpr auto a3_4 = std::to_array<std::uint8_t>({0x03, 0xc, 0xd, 0xe, 0xf});
    static_assert(ce_descriptor_view(a3_4).begin()->data_size() == 4);
    static_assert(ce_descriptor_view(a3_4).has_valid_bounds());
    CHECK(descriptor_view(a3_4).begin()->data_size() == 4);
    CHECK(descriptor_view(a3_4).has_valid_bounds());

    constexpr auto a0 = std::to_array<std::uint8_t>({0x00, 0xff});
    CHECK(!descriptor_view(a0).has_valid_bounds());
    constexpr auto a1 = std::to_array<std::uint8_t>({0x01});
    CHECK(!descriptor_view(a1).has_valid_bounds());
    constexpr auto a2 = std::to_array<std::uint8_t>({0x02});
    CHECK(!descriptor_view(a2).has_valid_bounds());
    constexpr auto a3 = std::to_array<std::uint8_t>({0x03, 0x01, 0x23, 0x45});
    CHECK(!descriptor_view(a3).has_valid_bounds());
}
