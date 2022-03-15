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
#ifndef __HID_REPORTS_OPAQUE_H_
#define __HID_REPORTS_OPAQUE_H_

#include "hid/rdf/all_items.h"
#include "hid/report.h"

namespace hid
{
	namespace reports
	{
	    namespace opaque
		{
            template<const unsigned BYTE_SIZE, const hid::report_type TYPE, const uint8_t REPORT_ID>
            struct report : public hid::report<report<BYTE_SIZE, TYPE, REPORT_ID>, TYPE, REPORT_ID>
            {
                std::array<uint8_t, BYTE_SIZE> payload {};
            };

            template<typename TReport, typename TUsage>
			static constexpr auto report_descriptor(TUsage use)
			{
				using namespace hid;
				using namespace hid::rdf;

				return (
                    report_size(8),
                    report_count(sizeof(TReport) - (TReport::ID > 0) ? 1 : 0),
                    logical_limits<1, 1>(0, 0xff),
                    usage_extended(use),
                    main::data_field<TReport::type()>::buffered_variable()
                );
			}
		};
	}
}

#endif // __HID_REPORTS_OPAQUE_H_
