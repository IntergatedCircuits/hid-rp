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
#ifndef __HID_USAGE_H_
#define __HID_USAGE_H_

#include <cstdint>
#include <limits>

namespace hid
{
    /// \brief Full identifier of a usage. Consists of 16 bits usage page ID and 16 bits usage index.
    using usage_id_type    = std::uint32_t;

    /// \brief Relative identifier of a usage within a usage page.
    using usage_index_type = std::uint16_t;

    constexpr usage_id_type    USAGE_INDEX_MASK   = std::numeric_limits<usage_index_type>::max();
    constexpr std::size_t      USAGE_PAGE_OFFSET  = (8 * sizeof(usage_index_type));
    constexpr usage_id_type    USAGE_PAGE_ID_MASK = std::numeric_limits<std::uint16_t>::max() << USAGE_PAGE_OFFSET;

    namespace rdf
    {
        namespace local
        {
            template<typename T>
            constexpr byte_type usage_size()
            {
                return (static_cast<usage_id_type>(T::MAX_USAGE) & USAGE_INDEX_MASK)
                    > std::numeric_limits<std::uint8_t>::max() ? 2 : 1;
            }
        }
        namespace global
        {
            template<typename T>
            constexpr byte_type usage_page_size()
            {
                return (static_cast<usage_id_type>(T::PAGE_ID) >> USAGE_PAGE_OFFSET) 
                    > std::numeric_limits<std::uint8_t>::max() ? 2 : 1;
            }
        }
    }

    class nullusage_t
    {
        // The usage page isn't encoded, so it's not a full usage type
    public:
        constexpr static usage_id_type MAX_USAGE = 0;
        constexpr nullusage_t()
        {
        }
        constexpr operator usage_index_type() const
        {
            return 0;
        }
        template<typename T>
        constexpr bool operator==(const T& rhs) const
        {
            return (static_cast<usage_id_type>(rhs) & USAGE_INDEX_MASK)
                == static_cast<usage_index_type>(*this);
        }
        template<typename T>
        constexpr bool operator!=(const T& rhs) const
        {
            return !(*this == rhs);
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

#endif // __HID_RDF_USAGE_H_
