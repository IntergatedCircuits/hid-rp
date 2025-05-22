/// @file
///
/// @author Benedek Kupper
/// @date   2024
///
/// @copyright
///         This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
///         If a copy of the MPL was not distributed with this file, You can obtain one at
///         https://mozilla.org/MPL/2.0/.
///
#ifndef __HID_APP_MOUSE_HPP_
#define __HID_APP_MOUSE_HPP_

#include "hid/page/button.hpp"
#include "hid/page/consumer.hpp"
#include "hid/page/generic_desktop.hpp"
#include "hid/rdf/descriptor.hpp"
#include "hid/report.hpp"
#include "hid/report_bitset.hpp"

namespace hid::app::mouse
{
template <uint8_t REPORT_ID = 0, std::size_t BUTTONS_COUNT = 3>
struct report : public hid::report::base<hid::report::type::INPUT, REPORT_ID>
{
    hid::report_bitset<page::button, page::button(1), page::button(BUTTONS_COUNT)> buttons;
    std::int8_t x{};
    std::int8_t y{};

    constexpr void reset_movement()
    {
        x = 0;
        y = 0;
    }
};

template <uint8_t REPORT_ID = 0, std::size_t BUTTONS_COUNT = 3>
static constexpr auto app_report_descriptor()
{
    using namespace hid::page;
    using namespace hid::rdf;

    // clang-format off
    return descriptor(
        usage_page<generic_desktop>(),
        usage(generic_desktop::MOUSE),
        collection::application(
            usage(generic_desktop::POINTER),
            collection::physical(
                conditional_report_id<REPORT_ID>(),
                // buttons
                usage_page<button>(),
                usage_limits(button(1), button(BUTTONS_COUNT)),
                logical_limits<1, 1>(0, 1),
                report_count(BUTTONS_COUNT),
                report_size(1),
                input::absolute_variable(),
                input::byte_padding<BUTTONS_COUNT>(),

                // relative directions
                usage_page<generic_desktop>(),
                usage(generic_desktop::X),
                usage(generic_desktop::Y),
                logical_limits<1, 1>(-127, 127),
                report_count(2),
                report_size(8),
                input::relative_variable()
            )
        )
    );
    // clang-format on
}

static constexpr uint8_t resolution_multiplier_bit_size()
{
    // https://github.com/qmk/qmk_firmware/issues/17585#issuecomment-1238023671
    return 2;
}

// https://learn.microsoft.com/en-us/previous-versions/windows/hardware/design/dn613912(v=vs.85)
// This item only takes two bits in the feature report, byte padding is the caller's responsibility!
template <uint8_t MULTIPLIER_MAX>
static constexpr auto resolution_multiplier()
{
    using namespace hid::page;
    using namespace hid::rdf;

    // clang-format off
    return descriptor(
        push_globals(),
        usage(generic_desktop::RESOLUTION_MULTIPLIER),
        logical_limits<1, 1>(0, 1),
        physical_limits<1, 1>(1, MULTIPLIER_MAX),
        report_count(1),
        report_size(resolution_multiplier_bit_size()),
        feature::absolute_variable(),
        pop_globals()
    );
    // clang-format on
}

// Use a report ID for Linux compatibility
// until https://bugzilla.kernel.org/show_bug.cgi?id=220144 is resolved
template <uint8_t MULTIPLIER_MAX, uint8_t REPORT_ID = 0>
struct resolution_multiplier_report
    : public hid::report::base<hid::report::type::FEATURE, REPORT_ID>
{
    std::uint8_t resolutions{};

    constexpr void reset() { resolutions = 0; }
    bool high_resolution() const { return resolutions != 0; }

    constexpr uint8_t vertical_scroll_multiplier() const
    {
        return (resolutions & 0x01) ? MULTIPLIER_MAX : 1;
    }
    constexpr uint8_t horizontal_scroll_multiplier() const
    {
        return (resolutions & 0x04) ? MULTIPLIER_MAX : 1;
    }
};

/// @brief Creates the descriptor block for high resolution scrolling for a mouse pointer
/// collection.
/// @note This descriptor block is assuming the current usage page is generic_desktop
/// @tparam MAX_SCROLL the maximum scroll value for Wheel and AC Pan usages
/// @tparam MULTIPLIER_MAX the maximum value of the resolution multiplier (valid range is 1-120)
/// @return the descriptor block
template <int16_t MAX_SCROLL, uint8_t MULTIPLIER_MAX>
static constexpr auto high_resolution_scrolling()
{
    using namespace hid::page;
    using namespace hid::rdf;
    constexpr uint8_t SCROLL_BYTES = MAX_SCROLL > std::numeric_limits<int8_t>::max() ? 2 : 1;

    // clang-format off
    return descriptor(
        collection::logical(
            usage(generic_desktop::WHEEL),
            logical_limits<SCROLL_BYTES>(-MAX_SCROLL, MAX_SCROLL),
            report_count(1),
            report_size(SCROLL_BYTES * 8),
            input::relative_variable(),
            resolution_multiplier<MULTIPLIER_MAX>()
        ),
        collection::logical(
            usage_extended(consumer::AC_PAN),
            // skip repeating the same global items as the Wheel usage
            input::relative_variable(),
            resolution_multiplier<MULTIPLIER_MAX>()
        ),
        feature::byte_padding<resolution_multiplier_bit_size() * 2>()
    );
    // clang-format on
}

} // namespace hid::app::mouse

#endif // __HID_APP_MOUSE_HPP_
