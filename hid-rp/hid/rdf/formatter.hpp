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
#ifndef __HID_RDF_FORMATTER_HPP_
#define __HID_RDF_FORMATTER_HPP_

#include <format>
#include "hid/page/all.hpp"
#include "hid/rdf/descriptor_view.hpp"
#include "hid/rdf/unit.hpp"

/// @brief  Formatter specialization for runtime usage types.
template <>
struct std::formatter<hid::usage_t>
{
  private:
    std::formatter<hid::usage_id_t> numeric_{};
    bool add_page_{};

  public:
    constexpr auto parse(std::format_parse_context& ctx)
    {
        auto pos = ctx.begin();
        // if the format's first symbol is p, the usage page is added
        if ((*pos == 'p') or (*pos == 'P'))
        {
            add_page_ = true;
            ctx.advance_to(pos + 1);
        }
        // the rest will be used for numeric formatting, if the usage is not named
        return numeric_.parse(ctx);
    }

    template <typename FormatContext>
    FormatContext::iterator format(const hid::usage_t& usage, FormatContext& ctx) const
    {
        auto info = hid::page::get_page_info(usage.page_id());
        if (add_page_)
        {
            if (info.valid_page())
            {
                format_to(ctx.out(), "{} / ", info.page_name);
            }
            else
            {
                format_to(ctx.out(), "{}({:#06x}) / ", info.page_name, usage.page_id());
            }
        }
        if (const char* name = info.get_usage_name(usage.id()); name)
        {
            return format_to(ctx.out(), "{}", name);
        }
        return numeric_.format(usage.id(), ctx);
    }
};

/// @brief  Formatter specialization for compile-time usage types.
/// @tparam T: usage concept type
template <hid::UsageType T>
struct std::formatter<T> : public std::formatter<hid::usage_t>
{};

#endif // __HID_RDF_FORMATTER_HPP_
