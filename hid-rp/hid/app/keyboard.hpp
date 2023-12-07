/// @file
///
/// @author Benedek Kupper
/// @date   2022
///
/// @copyright
///         This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
///         If a copy of the MPL was not distributed with this file, You can obtain one at
///         https://mozilla.org/MPL/2.0/.
///
#ifndef __HID_APP_KEYBOARD_HPP_
#define __HID_APP_KEYBOARD_HPP_

#include "hid/page/generic_desktop.hpp"
#include "hid/page/keyboard_keypad.hpp"
#include "hid/page/leds.hpp"
#include "hid/rdf/descriptor.hpp"
#include "hid/report.hpp"

namespace hid::app::keyboard
{
template <uint8_t REPORT_ID>
static constexpr auto keys_input_report_descriptor()
{
    using namespace hid::page;
    using namespace hid::rdf;

    // clang-format off
    return descriptor(
        conditional_report_id<REPORT_ID>(),
        // modifier byte
        report_size(1),
        report_count(8),
        logical_limits<1, 1>(0, 1),
        usage_page<keyboard_keypad>(),
        usage_limits(keyboard_keypad::LEFTCTRL, keyboard_keypad::RIGHTGUI),
        input::absolute_variable(),
        // reserved byte
        input::padding(8),
        // key codes
        report_size(8),
        report_count(6),
        logical_limits<1, 1>(0, keyboard_keypad::KEYPAD_HEXADECIMAL),
        usage_limits(nullusage, keyboard_keypad::KEYPAD_HEXADECIMAL),
        input::array()
    );
    // clang-format on
}

template <uint8_t REPORT_ID>
struct keys_input_report : public hid::report::base<hid::report::type::INPUT, REPORT_ID>
{
    uint8_t modifiers = 0;
    uint8_t reserved = 0;
    std::array<uint8_t, 6> scancodes = {};

    constexpr keys_input_report() = default;

    constexpr bool set_key_state(page::keyboard_keypad key, bool pressed)
    {
        using namespace hid::page;

        if (key >= keyboard_keypad::LEFTCTRL)
        {
            uint8_t mask =
                1 << (static_cast<uint8_t>(key) - static_cast<uint8_t>(keyboard_keypad::LEFTCTRL));
            if (pressed)
            {
                modifiers |= mask;
            }
            else
            {
                modifiers &= ~mask;
            }
            return true;
        }
        else if (pressed)
        {
            for (auto& code : scancodes)
            {
                if (code == 0)
                {
                    code = static_cast<uint8_t>(key);
                    return true;
                }
            }
            // scancodes buffer full, need to raise rollover error
            for (auto& code : scancodes)
            {
                code = static_cast<uint8_t>(keyboard_keypad::ERRORROLLOVER);
            }
            return false;
        }
        else
        {
            for (auto& code : scancodes)
            {
                if (code == static_cast<uint8_t>(key))
                {
                    code = 0;
                    return true;
                }
                // clear rollover error when a key is released
                else if (code == static_cast<uint8_t>(keyboard_keypad::ERRORROLLOVER))
                {
                    code = 0;
                }
            }
            return false;
        }
    }
};
static_assert(sizeof(keys_input_report<0>) == 8);
static_assert(sizeof(keys_input_report<1>) == 9);

template <uint8_t REPORT_ID>
static constexpr auto leds_output_report_descriptor()
{
    using namespace hid::page;
    using namespace hid::rdf;

    // clang-format off
    return descriptor(
        conditional_report_id<REPORT_ID>(),
        report_size(1),
        report_count(5),
        logical_limits<1, 1>(0, 1),
        usage_page<leds>(),
        usage_limits(leds::NUM_LOCK, leds::KANA),
        output::absolute_variable(),
        output::padding(3)
    );
    // clang-format on
}

template <uint8_t REPORT_ID>
struct output_report : public hid::report::base<hid::report::type::OUTPUT, REPORT_ID>
{
    uint8_t leds = 0;

    constexpr output_report() = default;

    constexpr bool get_led_state(page::leds led) const
    {
        return ((leds >> (static_cast<uint8_t>(led) - static_cast<uint8_t>(page::leds::NUM_LOCK))) &
                1) != 0;
    }
};

template <uint8_t REPORT_ID = 0>
static constexpr auto app_report_descriptor()
{
    using namespace hid::page;
    using namespace hid::rdf;

    // clang-format off
    return descriptor(
        usage_extended(generic_desktop::KEYBOARD),
        collection::application(
            // input keys report
            keys_input_report_descriptor<REPORT_ID>(),

            // LED report
            leds_output_report_descriptor<REPORT_ID>()
        )
    );
    // clang-format on
}

} // namespace hid::app::keyboard

#endif // __HID_APP_KEYBOARD_HPP_
