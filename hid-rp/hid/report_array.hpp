// SPDX-License-Identifier: MPL-2.0
#pragma once

#include <algorithm>
#include <array>
#include "sized_unsigned.hpp"

namespace hid
{

/// @brief  This class stores usages in an array, as a report field.
/// @tparam T the usage type
/// @tparam SIZE the maximum number of usages that can be stored
/// @tparam TStorage the storage type, which might be different from the usage type
template <typename T, std::size_t SIZE, typename TStorage = T>
class report_array
{
    using numeric_type =
        std::conditional_t<std::is_same_v<T, TStorage>, T, sized_unsigned_t<sizeof(T)>>;

  public:
    bool set(T usage, bool value = true)
    {
        auto num = static_cast<numeric_type>(usage);
        auto it = std::find(arr_.begin(), arr_.end(), value ? static_cast<numeric_type>(0) : num);
        if (it != arr_.end())
        {
            *it = value ? num : static_cast<numeric_type>(0);
            return true;
        }
        return false;
    }
    constexpr void reset() { arr_.fill(static_cast<numeric_type>(0)); }
    constexpr bool reset(T usage) { return set(usage, false); }
    constexpr bool flip(T usage) { return set(usage, !test(usage)); }
    [[nodiscard]] constexpr bool test(T usage) const
    {
        return std::find(arr_.begin(), arr_.end(), static_cast<numeric_type>(usage)) != arr_.end();
    }
    constexpr void fill(T usage) { arr_.fill(static_cast<numeric_type>(usage)); }
    constexpr report_array() = default;
    constexpr bool operator==(const report_array&) const = default;
    constexpr bool operator!=(const report_array&) const = default;

  private:
    std::array<TStorage, SIZE> arr_{};
};

} // namespace hid
