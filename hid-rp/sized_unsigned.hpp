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
#ifndef __SIZED_UNSIGNED_HPP_
#define __SIZED_UNSIGNED_HPP_

#include <cstdint>
#include <limits>
#include <type_traits>

/// @brief  Lookup unsigned integer of matching size
template <std::size_t SIZE, class T = void>
struct sized_integer
{};

template <std::size_t SIZE>
struct sized_integer<SIZE, std::enable_if_t<SIZE == 1>>
{
    typedef std::uint8_t unsigned_type;
    typedef std::int8_t signed_type;
};
template <std::size_t SIZE>
struct sized_integer<SIZE, std::enable_if_t<SIZE == 2>>
{
    typedef std::uint16_t unsigned_type;
    typedef std::int16_t signed_type;
};
template <std::size_t SIZE>
struct sized_integer<SIZE, std::enable_if_t<SIZE == 4>>
{
    typedef std::uint32_t unsigned_type;
    typedef std::int32_t signed_type;
};
template <std::size_t SIZE>
struct sized_integer<SIZE, std::enable_if_t<SIZE == 8>>
{
    typedef std::uint64_t unsigned_type;
    typedef std::int64_t signed_type;
};

template <std::size_t SIZE>
using sized_unsigned_t = typename sized_integer<SIZE>::unsigned_type;
template <std::size_t SIZE>
using sized_signed_t = typename sized_integer<SIZE>::signed_type;

template <typename T>
concept IntegerConvertable = std::is_convertible_v<T, sized_unsigned_t<sizeof(T)>>;

template <typename T>
constexpr inline std::size_t value_size(T c)
{
    if constexpr (std::is_signed_v<T>)
    {
        auto x = static_cast<std::int64_t>(c);
        if ((x < std::numeric_limits<std::int32_t>::min()) or
            (x > std::numeric_limits<std::int32_t>::max()))
        {
            return 8;
        }
        if ((x < std::numeric_limits<std::int16_t>::min()) or
            (x > std::numeric_limits<std::int16_t>::max()))
        {
            return 4;
        }
        if ((x < std::numeric_limits<std::int8_t>::min()) or
            (x > std::numeric_limits<std::int8_t>::max()))
        {
            return 2;
        }
        return 1;
    }
    // else
    {
        auto x = static_cast<std::uint64_t>(c);
        return (x > std::numeric_limits<std::uint32_t>::max())   ? 8
               : (x > std::numeric_limits<std::uint16_t>::max()) ? 4
               : (x > std::numeric_limits<std::uint8_t>::max())  ? 2
                                                                 : 1;
    }
}

#endif // __SIZED_UNSIGNED_HPP_
