// SPDX-License-Identifier: MPL-2.0
#pragma once

#include "hid/report_array.hpp"
#include "hid/report_bitset.hpp"
#include "print_hex_array.hpp"

// test-only pretty-printers for the boost::ut assertion output; found via ADL
namespace hid
{
template <auto MIN, auto MAX>
std::ostream& operator<<(std::ostream& os, const report_bitset_range<MIN, MAX>& value)
{
    return print_hex_array(os, value.raw());
}

template <auto... Keys>
std::ostream& operator<<(std::ostream& os, const report_bitset<Keys...>& value)
{
    return print_hex_array(os, value.raw());
}

template <typename T, std::size_t SIZE, typename TStorage>
std::ostream& operator<<(std::ostream& os, const report_array<T, SIZE, TStorage>& value)
{
    return print_hex_array(os, value.raw());
}
} // namespace hid
