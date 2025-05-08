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

template <typename TIterator>
struct std::formatter<hid::rdf::items_view_base<TIterator>>
{
  private:
    unsigned width_{};

  public:
    constexpr auto parse(std::format_parse_context& ctx)
    {
        if (ctx.begin() == ctx.end())
        {
            // return ctx.begin();
        }
        else if (std::from_chars(ctx.begin(), ctx.end(), width_).ec != std::errc{})
        {
            throw std::format_error("Invalid format specifier");
        }
        return ctx.begin();
    }

    template <typename FormatContext>
    FormatContext::iterator format(const hid::rdf::items_view_base<TIterator>& desc,
                                   FormatContext& ctx) const
    {
        for (const auto& item : desc)
        {
            switch (item.type())
            {
            case hid::rdf::item_type::MAIN:
                switch (item.main_tag())
                {
                case hid::rdf::main::tag::INPUT:
                    format_to(ctx.out(), "Input: ");
                    break;
                case hid::rdf::main::tag::OUTPUT:
                    format_to(ctx.out(), "Output: ");
                    break;
                case hid::rdf::main::tag::FEATURE:
                    format_to(ctx.out(), "Feature: ");
                    break;
                case hid::rdf::main::tag::COLLECTION:
                    format_to(ctx.out(), "Collection: ");
                    break;
                case hid::rdf::main::tag::END_COLLECTION:
                    format_to(ctx.out(), "End Collection: ");
                    break;
                default:
                    break;
                }
                break;
            case hid::rdf::item_type::GLOBAL:
                switch (item.global_tag())
                {
                case hid::rdf::global::tag::USAGE_PAGE:
                    format_to(ctx.out(), "Usage Page: ");
                    break;
                case hid::rdf::global::tag::LOGICAL_MINIMUM:
                    format_to(ctx.out(), "Logical Minimum({})", item.value_signed());
                    break;
                case hid::rdf::global::tag::LOGICAL_MAXIMUM:
                    format_to(ctx.out(), "Logical Maximum({})", item.value_signed());
                    break;
                case hid::rdf::global::tag::PHYSICAL_MINIMUM:
                    format_to(ctx.out(), "Physical Minimum({})", item.value_signed());
                    break;
                case hid::rdf::global::tag::PHYSICAL_MAXIMUM:
                    format_to(ctx.out(), "Physical Maximum({})", item.value_signed());
                    break;
                case hid::rdf::global::tag::UNIT_EXPONENT:
                    format_to(ctx.out(), "Unit Exponent({})", hid::rdf::unit::get_exponent(item));
                    break;
                case hid::rdf::global::tag::UNIT:
                    format_to(ctx.out(), "Unit: ");
                    break;
                case hid::rdf::global::tag::REPORT_SIZE:
                    format_to(ctx.out(), "Report Size: ");
                    break;
                case hid::rdf::global::tag::REPORT_ID:
                    format_to(ctx.out(), "Report ID: ");
                    break;
                case hid::rdf::global::tag::REPORT_COUNT:
                    format_to(ctx.out(), "Report Count: ");
                    break;
                case hid::rdf::global::tag::PUSH:
                    format_to(ctx.out(), "Push: ");
                    break;
                case hid::rdf::global::tag::POP:
                    format_to(ctx.out(), "Pop: ");
                    break;
                default:
                    break;
                }
                break;
            case hid::rdf::item_type::LOCAL:
                switch (item.local_tag())
                {
                case hid::rdf::local::tag::USAGE:
                    format_to(ctx.out(), "Usage: ");
                    break;
                case hid::rdf::local::tag::USAGE_MINIMUM:
                    format_to(ctx.out(), "Usage Minimum: ");
                    break;
                case hid::rdf::local::tag::USAGE_MAXIMUM:
                    format_to(ctx.out(), "Usage Maximum: ");
                    break;
                case hid::rdf::local::tag::DESIGNATOR_INDEX:
                    format_to(ctx.out(), "Designator Index: ");
                    break;
                case hid::rdf::local::tag::DESIGNATOR_MINIMUM:
                    format_to(ctx.out(), "Designator Minimum: ");
                    break;
                case hid::rdf::local::tag::DESIGNATOR_MAXIMUM:
                    format_to(ctx.out(), "Designator Maximum: ");
                    break;
                case hid::rdf::local::tag::STRING_INDEX:
                    format_to(ctx.out(), "String Index: ");
                    break;
                case hid::rdf::local::tag::STRING_MINIMUM:
                    format_to(ctx.out(), "String Minimum: ");
                    break;
                case hid::rdf::local::tag::STRING_MAXIMUM:
                    format_to(ctx.out(), "String Maximum: ");
                    break;
                case hid::rdf::local::tag::DELIMITER:
                    format_to(ctx.out(), "Delimiter: ");
                    break;
                default:
                    format_to(ctx.out(), "Unknown: ");
                    break;
                }
                break;
            default:
                format_to(ctx.out(), "Unknown: ");
                break;
            }
        }
    }
};

#endif // __HID_RDF_FORMATTER_HPP_
