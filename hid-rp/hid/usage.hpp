/// @file
///
/// @author Benedek Kupper
/// @date   2025
///
/// @copyright
///         This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
///         If a copy of the MPL was not distributed with this file, You can obtain one at
///         https://mozilla.org/MPL/2.0/.
///
#ifndef __HID_USAGE_HPP_
#define __HID_USAGE_HPP_

#include <compare>
#include <cstdint>
#include <limits>

namespace hid
{
using page_id_t = std::uint16_t;
using usage_id_t = std::uint16_t;

namespace page
{
struct info
{
  private:
    const char* (*const get_usage_name_)(hid::usage_id_t id);

  public:
    const char* const page_name;
    const page_id_t page_id;
    const usage_id_t max_usage_id;

    constexpr info(page_id_t page, usage_id_t max, const char* name,
                   const char* (*get_name)(hid::usage_id_t id) = nullptr)
        : page_name(name), get_usage_name_(get_name), page_id(page), max_usage_id(max)
    {}

    const char* get_usage_name(usage_id_t id) const
    {
        if (get_usage_name_)
        {
            return get_usage_name_(id);
        }
        return nullptr;
    }

    constexpr bool operator==(const info& other) const { return page_id == other.page_id; }
    constexpr bool operator!=(const info& other) const = default;
    constexpr bool valid_page() const { return page_id != 0; }
};

/// @brief Each usage page type needs the specialization of this template method
///        for this library to function correctly.
template <typename T>
constexpr inline auto get_info()
{
    return info(0, 0, "unknown");
}

} // namespace page

/// @brief This concept matches types with valid page information,
///        which is necessary for determining the full usage value.
template <typename T>
concept UsageType = (sizeof(T) <= sizeof(usage_id_t)) and (page::get_info<T>().page_id > 0);

namespace rdf::global
{
template <UsageType T>
constexpr std::size_t usage_page_size()
{
    return page::get_info<T>().page_id > std::numeric_limits<std::uint8_t>::max() ? 2 : 1;
}
} // namespace rdf::global

/// @brief The usage_t class holds the entire usage information in one class,
///        combining the page ID and usage ID into a single 32-bit variable.
class usage_t
{
  public:
    using type = std::uint32_t;

    constexpr explicit usage_t(type value)
        : value_(value)
    {}
    constexpr usage_t(page_id_t page, usage_id_t u)
        : value_((page << 16) | u)
    {}
    template <UsageType T>
    constexpr usage_t(T u)
        : value_((page::get_info<T>().page_id << 16) | static_cast<type>(u))
    {}
    constexpr operator type&() { return value_; }
    constexpr operator type() const { return value_; }
    constexpr page_id_t page_id() const { return value_ >> 16; }
    constexpr usage_id_t id() const { return value_ & std::numeric_limits<usage_id_t>::max(); }

    constexpr auto operator<=>(const usage_t&) const = default;

  private:
    type value_;
};

/// @brief Type and variable that expresses a never valid null usage state.
class nullusage_t : public usage_t
{
  public:
    constexpr nullusage_t()
        : usage_t(0)
    {}
};
constexpr nullusage_t nullusage;

namespace page
{
// alias definition to simplify descriptor definition
using hid::nullusage;
} // namespace page

} // namespace hid

#endif // __HID_RDF_USAGE_HPP_
