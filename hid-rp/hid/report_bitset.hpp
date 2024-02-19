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
#ifndef __HID_REPORT_BITSET_HPP_
#define __HID_REPORT_BITSET_HPP_

#include <array>
#include <cassert>
#include "hid/usage.hpp"

namespace hid::report
{

/// @brief  This class stores usages in a bitset, as a report field.
/// @tparam T the usage type
/// @tparam MIN the minimum usage to be stored on a bit
/// @tparam MAX the maximum usage to be stored on a bit
template <UsageType T, T MIN, T MAX>
class bitset
{
  public:
    constexpr static T min() { return MIN; }
    constexpr static T max() { return MAX; }
    static_assert(min() <= max());
    constexpr static std::size_t size()
    {
        return static_cast<std::size_t>(max()) - static_cast<std::size_t>(min()) + 1;
    }

    constexpr bool in_range(T usage) const { return (usage >= min()) and (usage <= max()); }
    constexpr bool set(T usage, bool value = true)
    {
        if (in_range(usage))
        {
            auto n = static_cast<usage_id_t>(usage) - static_cast<usage_id_t>(min());
            if (value)
            {
                bits_[n / 8] |= 1 << (n % 8);
            }
            else
            {
                bits_[n / 8] &= ~(1 << (n % 8));
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    constexpr void reset() { bits_.fill(0); }
    constexpr bool reset(T usage) { return set(usage, false); }
    constexpr bool flip(T usage) { return set(usage, !test(usage)); }
    bool test(T usage) const
    {
        if (in_range(usage))
        {
            auto n = static_cast<usage_id_t>(usage) - static_cast<usage_id_t>(min());
            return bits_[n / 8] & (1 << (n % 8));
        }
        assert(false);
        return false;
    }
    constexpr bitset() = default;

    constexpr bool operator==(const bitset&) const = default;
    constexpr bool operator!=(const bitset&) const = default;

  private:
    std::array<std::uint8_t, (size() + 7) / 8> bits_{};
};

} // namespace hid::report

#endif // __HID_REPORT_BITSET_HPP_
