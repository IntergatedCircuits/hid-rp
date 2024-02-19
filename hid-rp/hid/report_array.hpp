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
#ifndef __HID_REPORT_ARRAY_HPP_
#define __HID_REPORT_ARRAY_HPP_

#include <algorithm>
#include <array>
#include "hid/usage.hpp"

namespace hid::report
{

/// @brief  This class stores usages in an array, as a report field.
/// @tparam T the usage type
/// @tparam SIZE the maximum number of usages that can be stored
/// @tparam TStorage the storage type, which might be different from the usage type
template <UsageType T, std::size_t SIZE, typename TStorage = T>
class array
{
  public:
    bool set(T usage, bool value = true)
    {
        auto n = static_cast<TStorage>(usage);
        auto it = std::find(arr_.begin(), arr_.end(), value ? static_cast<TStorage>(0) : n);
        if (it != arr_.end())
        {
            *it = value ? n : static_cast<TStorage>(0);
            return true;
        }
        return false;
    }
    constexpr void reset() { arr_.fill(static_cast<TStorage>(0)); }
    constexpr bool reset(T usage) { return set(usage, false); }
    constexpr bool flip(T usage) { return set(usage, !test(usage)); }
    bool test(T usage) const
    {
        return std::find(arr_.begin(), arr_.end(), static_cast<TStorage>(usage)) != arr_.end();
    }
    constexpr void fill(T usage) { arr_.fill(static_cast<TStorage>(usage)); }
    constexpr array() = default;

    constexpr bool operator==(const array&) const = default;
    constexpr bool operator!=(const array&) const = default;

  private:
    std::array<TStorage, SIZE> arr_{};
};

} // namespace hid::report

#endif // __HID_REPORT_ARRAY_HPP_
