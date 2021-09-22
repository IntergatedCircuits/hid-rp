/// \file
///
/// \author Benedek Kupper
/// \date   2021
///
/// \copyright
///         This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
///         If a copy of the MPL was not distributed with this file, You can obtain one at
///         https://mozilla.org/MPL/2.0/.
///
#ifndef __HID_USAGE_H_
#define __HID_USAGE_H_

#include "constants.h"

namespace hid
{
    using usage_id_type = std::uint16_t;
    using usage_ext_id_type = std::uint32_t;

    constexpr usage_ext_id_type USAGE_ID_MASK      = std::numeric_limits<usage_id_type>::max();
    constexpr std::size_t       USAGE_PAGE_OFFSET  = (8 * sizeof(usage_id_type));
    constexpr usage_ext_id_type USAGE_PAGE_ID_MASK = USAGE_ID_MASK << USAGE_PAGE_OFFSET;

    namespace rdf
    {
        template<typename T>
        constexpr byte_type usage_size()
        {
            return (static_cast<usage_ext_id_type>(T::MAX_USAGE) & USAGE_ID_MASK) > 0xff ? 2 : 1;
        }

        template<typename T>
        constexpr byte_type usage_page_size()
        {
            return (static_cast<local::usage_ext_id_type>(T::PAGE_ID) >> local::USAGE_PAGE_OFFSET) > 0xff ? 2 : 1;
        }
    }

    class nullusage_t
    {
    public:
        constexpr static usage_ext_id_type MAX_USAGE = 0;
        constexpr nullusage_t()
        {
        }
        constexpr operator usage_id_type() const
        {
            return 0;
        }
    };

    /// \brief Variable that expresses null usage state (for usage_limits min)
    constexpr nullusage_t nullusage;

    /// Usage types can either be an enum type, where the enum has:
    /// * \ref usage_ext_id_type underlying type
    /// * PAGE_ID = the page ID shifted with USAGE_PAGE_OFFSET
    /// * MAX_USAGE = the highest usage ID in extended format (encoding the usage page)
    ///
    /// OR a class type which:
    /// * defines conversion operator to \ref usage_ext_id_type
    /// * defines constexpr static usage_ext_id_type PAGE_ID
    /// * defines constexpr static usage_ext_id_type MAX_USAGE
    ///
}

#endif // __HID_USAGE_H_
