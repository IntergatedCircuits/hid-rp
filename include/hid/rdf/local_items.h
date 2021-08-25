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

namespace hid
{
    namespace rdf
    {
        /// The supplied value can either be an enum type, where the enum has:
        /// * \ref usage_ext_id_type underlying type
        /// * _PAGE_ID_SIZE = byte size of the page ID (1 or 2)
        /// * _MAX_ID_SIZE = byte size of the highest usage ID in use on this usage page
        ///
        /// OR a class type which:
        /// * defines conversion operator to \ref usage_ext_id_type
        /// * defines constexpr static byte_type _PAGE_ID_SIZE
        /// * defines constexpr static byte_type _MAX_ID_SIZE
        ///

        template<const byte_type DATA_SIZE = 2, typename T>
        constexpr auto usage(T value)
        {
            constexpr std::size_t ID_SIZE = std::min(static_cast<byte_type>(T::_MAX_ID_SIZE), DATA_SIZE);
            static_assert((ID_SIZE > 0) && (ID_SIZE <= sizeof(local::usage_id_type)));
            return short_item<ID_SIZE>(local::tag::USAGE, static_cast<local::usage_id_type>(value));
        }

        /// extended usage contains the usage page as well, otherwise the global usage page is considered
        template<typename T>
        constexpr auto usage_extended(T value)
        {
            constexpr std::size_t EXT_ID_SIZE = sizeof(local::usage_ext_id_type);
            return short_item<EXT_ID_SIZE>(local::tag::USAGE, static_cast<local::usage_ext_id_type>(value));
        }

        // usages are local items, there must be a min-max pair each time
        template<const byte_type DATA_MIN_SIZE = 2, const byte_type DATA_MAX_SIZE = 2, typename T>
        constexpr auto usage_limits(T min, T max)
        {
            constexpr std::size_t MIN_ID_SIZE = std::min(static_cast<byte_type>(T::_MAX_ID_SIZE), DATA_MIN_SIZE);
            constexpr std::size_t MAX_ID_SIZE = std::min(static_cast<byte_type>(T::_MAX_ID_SIZE), DATA_MAX_SIZE);
            static_assert((MIN_ID_SIZE > 0) && (MIN_ID_SIZE <= sizeof(local::usage_id_type)));
            static_assert((MAX_ID_SIZE > 0) && (MAX_ID_SIZE <= sizeof(local::usage_id_type)));
            return short_item<MIN_ID_SIZE>(local::tag::USAGE_MINIMUM, static_cast<local::usage_id_type>(min)),
                short_item<MAX_ID_SIZE>(local::tag::USAGE_MAXIMUM, static_cast<local::usage_id_type>(max));
        }

        template<typename T>
        constexpr auto usage_extended_limits(T min, T max)
        {
            constexpr std::size_t EXT_ID_SIZE = sizeof(local::usage_ext_id_type);
            return short_item<EXT_ID_SIZE>(local::tag::USAGE_MINIMUM, static_cast<local::usage_ext_id_type>(min)),
                short_item<EXT_ID_SIZE>(local::tag::USAGE_MAXIMUM, static_cast<local::usage_ext_id_type>(max));
        }
    }
}

#endif // __HID_RDF_LOCAL_ITEMS_H_
