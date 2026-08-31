// SPDX-License-Identifier: MPL-2.0
#pragma once

#include <array>
#include <cassert>
#include "hid/report.hpp"
#include "hid/usage.hpp"
#include "sized_unsigned.hpp"
#include <type_traits>

namespace hid
{

/// @brief  This class stores a range of usages in a bitset, as a report field.
/// @tparam MIN the minimum usage to be stored on a bit
/// @tparam MAX the maximum usage to be stored on a bit
template <auto MIN, auto MAX>
class report_bitset_range
{
    using T = decltype(MIN);
    static_assert(std::is_same_v<T, decltype(MAX)>,
                  "report_bitset_range: MIN and MAX must be the same type");
    using numeric_type = sized_unsigned_t<sizeof(T)>;

  public:
    constexpr static T min() { return MIN; }
    constexpr static T max() { return MAX; }
    static_assert(min() <= max());
    constexpr static std::size_t size()
    {
        return static_cast<std::size_t>(max()) - static_cast<std::size_t>(min()) + 1;
    }

    [[nodiscard]] constexpr bool in_range(T usage) const
    {
        return (usage >= min()) and (usage <= max());
    }
    constexpr bool set(T usage, bool value = true)
    {
        if (in_range(usage))
        {
            numeric_type num = static_cast<numeric_type>(usage) - static_cast<numeric_type>(min());
            if (value)
            {
                bits_[num / 8] |= 1 << (num % 8);
            }
            else
            {
                bits_[num / 8] &= ~(1 << (num % 8));
            }
            return true;
        }
        return false;
    }
    constexpr void reset() { bits_.fill(0); }
    constexpr bool reset(T usage) { return set(usage, false); }
    constexpr bool flip(T usage) { return set(usage, !test(usage)); }
    [[nodiscard]] constexpr bool test(T usage) const
    {
        if (in_range(usage))
        {
            numeric_type num = static_cast<numeric_type>(usage) - static_cast<numeric_type>(min());
            return bits_[num / 8] & (1 << (num % 8));
        }
        assert(false);
        return false;
    }
    constexpr report_bitset_range() = default;
    constexpr bool operator==(const report_bitset_range&) const = default;
    constexpr bool operator!=(const report_bitset_range&) const = default;

    // exposes the raw storage for test-only printing (see test/report_printers.hpp)
    [[nodiscard]] constexpr const auto& raw() const { return bits_; }

  private:
    std::array<std::uint8_t, (size() + 7) / 8> bits_{};
};

/// @brief  This class stores a list of usages in a bitset, as a report field.
/// @tparam Keys the usages to be stored, one per bit, in the given order
template <auto... Keys>
class report_bitset
{
    static_assert((UsageType<decltype(Keys)> and ...),
                  "report_bitset: all keys must be valid HID usage values");
    static constexpr std::array<usage_t, sizeof...(Keys)> keys{usage_t(Keys)...};

  public:
    constexpr static std::size_t size() { return sizeof...(Keys); }

    template <UsageType T>
    [[nodiscard]] constexpr bool contains(T usage) const
    {
        return index_of(usage) < size();
    }

    template <UsageType T>
    constexpr bool set(T usage, bool value = true)
    {
        std::size_t index = index_of(usage);
        if (index < size())
        {
            set_bit(index, value);
            return true;
        }
        return false;
    }
    template <auto USAGE>
    constexpr void set(bool value = true)
    {
        set_bit(index_of<USAGE>(), value);
    }
    constexpr void reset() { bits_.fill(0); }
    template <UsageType T>
    constexpr bool reset(T usage)
    {
        return set(usage, false);
    }
    template <auto USAGE>
    constexpr void reset()
    {
        set<USAGE>(false);
    }
    template <UsageType T>
    constexpr bool flip(T usage)
    {
        return set(usage, !test(usage));
    }
    template <auto USAGE>
    constexpr void flip()
    {
        set<USAGE>(!test<USAGE>());
    }
    template <UsageType T>
    [[nodiscard]] constexpr bool test(T usage) const
    {
        std::size_t index = index_of(usage);
        assert(index < size());
        return test_bit(index);
    }
    template <auto USAGE>
    [[nodiscard]] constexpr bool test() const
    {
        return test_bit(index_of<USAGE>());
    }

    constexpr report_bitset() = default;
    constexpr bool operator==(const report_bitset&) const = default;
    constexpr bool operator!=(const report_bitset&) const = default;

    // exposes the raw storage for test-only printing (see test/report_printers.hpp)
    [[nodiscard]] constexpr const auto& raw() const { return bits_; }

  private:
    template <UsageType T>
    [[nodiscard]] constexpr static std::size_t index_of(T usage)
    {
        usage_t u(usage);
        for (std::size_t i = 0; i < size(); ++i)
        {
            if (keys[i] == u)
            {
                return i;
            }
        }
        return size();
    }

    template <auto USAGE>
    [[nodiscard]] constexpr static std::size_t index_of()
    {
        constexpr std::size_t index = index_of(USAGE);
        static_assert(index < size(), "report_bitset: usage isn't part of the value list");
        return index;
    }

    static consteval bool has_duplicates()
    {
        for (std::size_t i = 0; i < keys.size(); ++i)
        {
            for (std::size_t j = i + 1; j < keys.size(); ++j)
            {
                if (keys[i] == keys[j])
                {
                    return true;
                }
            }
        }
        return false;
    }
    static_assert(not has_duplicates(), "report_bitset: duplicate usage in the value list");

    constexpr void set_bit(std::size_t index, bool value)
    {
        if (value)
        {
            bits_[index / 8] |= 1 << (index % 8);
        }
        else
        {
            bits_[index / 8] &= ~(1 << (index % 8));
        }
    }
    [[nodiscard]] constexpr bool test_bit(std::size_t index) const
    {
        return bits_[index / 8] & (1 << (index % 8));
    }

    std::array<std::uint8_t, (size() + 7) / 8> bits_{};
};

} // namespace hid
