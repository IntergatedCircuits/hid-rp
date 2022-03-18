/// \file
///
/// \author Benedek Kupper
/// \date   2022
///
/// \copyright
///         This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
///         If a copy of the MPL was not distributed with this file, You can obtain one at
///         https://mozilla.org/MPL/2.0/.
///
#ifndef __HID_REPORTS_KEYBOARD_H_
#define __HID_REPORTS_KEYBOARD_H_

#include <array>
#include "hid/rdf/all_items.h"
#include "hid/page/generic_desktop.h"
#include "hid/page/keyboard_keypad.h"
#include "hid/page/leds.h"
#include "hid/report.h"

namespace hid
{
	namespace reports
	{
	    namespace keyboard
	    {
	        template<const uint8_t REPORT_ID>
            static constexpr auto keys_input_report_descriptor()
	        {
                using namespace hid;
                using namespace hid::page;
                using namespace hid::rdf;

                return (
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
                    logical_limits<1, 1>(0, 0xff),
                    usage_limits(nullusage, keyboard_keypad::KEYPAD_HEXADECIMAL),
                    input::array()
                );
	        }

	        template<const uint8_t REPORT_ID>
	        struct keys_input_report : public report<report_type::INPUT, REPORT_ID>
	        {
	            uint8_t modifiers = 0;
	            uint8_t reserved = 0;
	            std::array<uint8_t, 6> scancodes = {};

                constexpr bool set_key_state(hid::page::keyboard_keypad key, bool pressed)
                {
                    using namespace hid::page;

                    if (key >= keyboard_keypad::LEFTCTRL)
                    {
                        uint8_t mask = 1 << (static_cast<uint8_t>(key) - static_cast<uint8_t>(keyboard_keypad::LEFTCTRL));
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
                        for (auto &code : scancodes)
                        {
                            if (code == 0)
                            {
                                code = static_cast<uint8_t>(key);
                                return true;
                            }
                        }
                        // scancodes buffer full, need to raise rollover error
                        for (auto &code : scancodes)
                        {
                            code = static_cast<uint8_t>(keyboard_keypad::ERRORROLLOVER);
                        }
                        return false;
                    }
                    else
                    {
                        for (auto &code : scancodes)
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

            template<const uint8_t REPORT_ID>
            static constexpr auto leds_output_report_descriptor()
            {
                using namespace hid;
                using namespace hid::page;
                using namespace hid::rdf;

                return (
                    conditional_report_id<REPORT_ID>(),
                    report_size(1),
                    report_count(5),
                    logical_limits<1, 1>(0, 1),
                    usage_page<leds>(),
                    usage_limits(leds::NUM_LOCK, leds::KANA),
                    output::absolute_variable(),
                    output::padding(3)
                );
            }

	        template<const uint8_t REPORT_ID>
	        struct output_report : public report<report_type::OUTPUT, REPORT_ID>
	        {
	            uint8_t leds = 0;

	            constexpr bool get_led_state(hid::page::leds led) const
	            {
	                return ((leds >> (static_cast<uint8_t>(led) - static_cast<uint8_t>(hid::page::leds::NUM_LOCK))) & 1) != 0;
	            }
	        };

            template<const uint8_t REPORT_ID>
            static constexpr auto app_report_descriptor()
            {
                using namespace hid;
                using namespace hid::page;
                using namespace hid::rdf;

                return (
                    usage_extended(generic_desktop::KEYBOARD),
                    collection::application(
                        // input keys report
                        keys_input_report_descriptor<REPORT_ID>(),

                        // LED report
                        leds_output_report_descriptor<REPORT_ID>()
                    )
                );
            }
	    }
	}
}

#endif // __HID_REPORTS_KEYBOARD_H_
