#include "hid/report_protocol.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("test your descriptor here")
{
    // Step 1: insert your descriptor here
    static constexpr auto desc = std::to_array<std::uint8_t>({
        0x05, 0x01, // USAGE_PAGE (Generic Desktop)
        0x09, 0x02, // USAGE (Mouse)
        0xa1, 0x01, // COLLECTION (Application)
        0x09, 0x01, //   USAGE (Pointer)
        0xa1, 0x00, //   COLLECTION (Physical)
        0x05, 0x09, //     USAGE_PAGE (Buttons)
        0x19, 0x01, //     USAGE_MINIMUM (Button 1)
        0x29, 0x03, //     USAGE_MAXIMUM (Button 3)
        0x15, 0x00, //     LOGICAL_MINIMUM (0)
        0x25, 0x01, //     LOGICAL_MAXIMUM (1)
        0x95, 0x03, //     REPORT_COUNT (3)
        0x75, 0x01, //     REPORT_SIZE (1)
        0x81, 0x02, //     INPUT (Data,Var,Abs)
        0x95, 0x01, //     REPORT_COUNT (1)
        0x75, 0x05, //     REPORT_SIZE (5)
        0x81, 0x03, //     INPUT (Cnst,Var,Abs)
        0x05, 0x01, //     USAGE_PAGE (Generic Desktop)
        0x09, 0x30, //     USAGE (X)
        0x09, 0x31, //     USAGE (Y)
        0x15, 0x81, //     LOGICAL_MINIMUM (-127)
        0x25, 0x7f, //     LOGICAL_MAXIMUM (127)
        0x75, 0x08, //     REPORT_SIZE (8)
        0x95, 0x02, //     REPORT_COUNT (2)
        0x81, 0x06, //     INPUT (Data,Var,Rel)
        0xc0,       //   END_COLLECTION
        0xc0        // END_COLLECTION
    });

    constexpr auto rp = hid::report_protocol(desc);

    // Step 2: check the report protocol properties, such as byte size and report id
    static_assert(rp.max_input_id == 0);
    static_assert(rp.max_input_size == 3);
    static_assert(rp.max_feature_id == 0);
    static_assert(rp.max_feature_size == 0);
    static_assert(rp.max_output_id == 0);
    static_assert(rp.max_output_size == 0);

    // Step 3: build this file to verify the descriptor (running the test is not needed)
}
