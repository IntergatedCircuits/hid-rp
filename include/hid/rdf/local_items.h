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
#ifndef __HID_RDF_LOCAL_ITEMS_H_
#define __HID_RDF_LOCAL_ITEMS_H_

#include "short_item.h"
#include "../usage.h"

namespace hid::rdf
{
    template<const byte_type DATA_SIZE = 2, typename T>
    constexpr auto usage(T value)
    {
        constexpr std::size_t ID_SIZE = std::min(local::usage_size<T>(), DATA_SIZE);
        static_assert((ID_SIZE > 0) and (ID_SIZE <= sizeof(usage_index_type)));
        return short_item<ID_SIZE>(local::tag::USAGE, static_cast<usage_index_type>(value));
    }

    /// \note  Extended usage contains the usage page as well, otherwise the global usage page is considered.
    ///        Extended usage is identified not by tag, but by the data size of the item.
    template<typename T>
    constexpr auto usage_extended(T value)
    {
        constexpr std::size_t EXT_ID_SIZE = sizeof(usage_id_type);
        return short_item<EXT_ID_SIZE>(local::tag::USAGE, static_cast<usage_id_type>(value));
    }

    /// \note  Usages are local items, there must be a min-max pair each time
    ///        (hence no definition for usage_min or usage_max).
    template<const byte_type DATA_MIN_SIZE = 2, const byte_type DATA_MAX_SIZE = 2, typename T>
    constexpr auto usage_limits(T min, T max)
    {
        constexpr std::size_t MIN_ID_SIZE = std::min(local::usage_size<T>(), DATA_MIN_SIZE);
        constexpr std::size_t MAX_ID_SIZE = std::min(local::usage_size<T>(), DATA_MAX_SIZE);
        static_assert((MIN_ID_SIZE > 0) and (MIN_ID_SIZE <= sizeof(usage_index_type)));
        static_assert((MAX_ID_SIZE > 0) and (MAX_ID_SIZE <= sizeof(usage_index_type)));
        return short_item<MIN_ID_SIZE>(local::tag::USAGE_MINIMUM, static_cast<usage_index_type>(min)),
            short_item<MAX_ID_SIZE>(local::tag::USAGE_MAXIMUM, static_cast<usage_index_type>(max));
    }

    template<const byte_type DATA_MAX_SIZE = 2, typename T>
    constexpr auto usage_limits(nullusage_t min, T max)
    {
        constexpr std::size_t MIN_ID_SIZE = 1;
        constexpr std::size_t MAX_ID_SIZE = std::min(local::usage_size<T>(), DATA_MAX_SIZE);
        static_assert((MAX_ID_SIZE > 0) and (MAX_ID_SIZE <= sizeof(usage_index_type)));
        return short_item<MIN_ID_SIZE>(local::tag::USAGE_MINIMUM, static_cast<usage_index_type>(min)),
            short_item<MAX_ID_SIZE>(local::tag::USAGE_MAXIMUM, static_cast<usage_index_type>(max));
    }

    template<typename T>
    constexpr auto usage_extended_limits(T min, T max)
    {
        constexpr std::size_t EXT_ID_SIZE = sizeof(usage_id_type);
        return short_item<EXT_ID_SIZE>(local::tag::USAGE_MINIMUM, static_cast<usage_id_type>(min)),
            short_item<EXT_ID_SIZE>(local::tag::USAGE_MAXIMUM, static_cast<usage_id_type>(max));
    }

    template<typename T>
    constexpr auto usage_extended_limits(nullusage_t min, T max)
    {
        constexpr std::size_t EXT_ID_SIZE = sizeof(usage_id_type);
        return short_item<EXT_ID_SIZE>(local::tag::USAGE_MINIMUM, static_cast<usage_id_type>(max) & USAGE_PAGE_ID_MASK),
            short_item<EXT_ID_SIZE>(local::tag::USAGE_MAXIMUM, static_cast<usage_id_type>(max));
    }

} // namespace hid::rdf

#endif // __HID_RDF_LOCAL_ITEMS_H_
