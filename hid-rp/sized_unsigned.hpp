// SPDX-License-Identifier: MPL-2.0
#ifndef __SIZED_UNSIGNED_HPP_
#define __SIZED_UNSIGNED_HPP_

#include <bitfilled/integer.hpp>
#include <bitfilled/size.hpp>

template <std::size_t SIZE>
using sized_unsigned_t = bitfilled::sized_unsigned_t<SIZE>;

template <std::size_t SIZE, bitfilled::Integral T = sized_unsigned_t<std::bit_ceil(SIZE)>>
using packed_integer = bitfilled::packed_integer<std::endian::little, SIZE, T>;

template <typename T>
inline constexpr auto byte_width(T value)
{
    return bitfilled::byte_width(value);
}

#endif // __SIZED_UNSIGNED_HPP_
