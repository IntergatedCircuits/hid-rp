// SPDX-License-Identifier: MPL-2.0
#pragma once

#include <array>
#include <charconv>
#include <ostream>

// prints an array of unsigned integers as a fixed-width hex sequence, one group per element
template <typename T, std::size_t N>
std::ostream& print_hex_array(std::ostream& os, const std::array<T, N>& values)
{
    constexpr std::size_t width = sizeof(T) * 2;
    for (auto value : values)
    {
        std::array<char, width> digits;
        auto [ptr, ec] = std::to_chars(digits.begin(), digits.end(), value, 16);
        auto length = static_cast<std::size_t>(ptr - digits.begin());
        for (std::size_t i = length; i < width; ++i)
        {
            os << '0';
        }
        os.write(digits.data(), static_cast<std::streamsize>(length));
    }
    return os;
}
