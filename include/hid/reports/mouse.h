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
#ifndef __HID_REPORTS_MOUSE_H_
#define __HID_REPORTS_MOUSE_H_

#include "hid/rdf/all_items.h"
#include "hid/page/generic_desktop.h"
#include "hid/page/button.h"
#include "hid/report.h"

namespace hid
{
	namespace reports
	{
	    namespace mouse
		{
            template<const uint8_t REPORT_ID>
            struct report : public hid::report<report_type::INPUT, REPORT_ID>
            {
                uint8_t buttons = 0;
                int8_t x = 0;
                int8_t y = 0;

                constexpr void set_button_state(hid::page::button b, bool pressed)
                {
                    uint8_t mask = 1 << (static_cast<uint8_t>(b) - 1);
                    if (pressed)
                    {
                        buttons |= mask;
                    }
                    else
                    {
                        buttons &= ~mask;
                    }
                }
                constexpr void reset_movement()
                {
                    x = 0;
                    y = 0;
                }
            };

            template<const uint8_t REPORT_ID = 0>
			static constexpr auto app_report_descriptor()
			{
				using namespace hid;
				using namespace hid::page;
				using namespace hid::rdf;

				return (
                    usage_page<generic_desktop>(),
                    usage(generic_desktop::MOUSE),
                    collection::application(
                        usage(generic_desktop::POINTER),
                        collection::physical(
                            conditional_report_id<REPORT_ID>(),
                            // buttons
                            usage_extended_limits(button(1), button(3)),
                            logical_limits<1, 1>(0, 1),
                            report_count(3),
                            report_size(1),
                            input::absolute_variable(),
                            input::padding(5),

                            // relative directions
                            usage(generic_desktop::X),
                            usage(generic_desktop::Y),
                            logical_limits<1, 1>(-127, 127),
                            report_count(2),
                            report_size(8),
                            input::relative_variable()
                        )
                    )
                );
			}
		};
	}
}

#endif // __HID_REPORTS_MOUSE_H_
