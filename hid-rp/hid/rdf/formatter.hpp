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
#include "hid/rdf/main_items.hpp"
#include "hid/rdf/parser.hpp"
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
        // first the page is printed, if requested
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
        // second the base usage is printed
        auto value = usage.id() & ~info.ius_mask;
        if (const char* name = info.get_usage_name(value); name)
        {
            vformat_to(ctx.out(), name, make_format_args(value));
        }
        else
        {
            numeric_.format(value, ctx);
        }
        // finally the inline usage switch is printed, if any
        if (const char* name = info.get_usage_name(usage.id() & info.ius_mask); name)
        {
            format_to(ctx.out(), " {}", name);
        }
        return ctx.out();
    }
};

/// @brief  Formatter specialization for compile-time usage types.
/// @tparam T: usage concept type
template <hid::UsageType T>
struct std::formatter<T> : public std::formatter<hid::usage_t>
{};

/// @brief  Formatter specialization for HID main item field types.
template <>
struct std::formatter<hid::rdf::main::field_type> : public std::formatter<string_view>
{
  public:
    template <typename FormatContext>
    FormatContext::iterator format(const hid::rdf::main::field_type& field,
                                   FormatContext& ctx) const
    {
        using namespace hid::rdf;
        format_to(ctx.out(), "{},{},{}",
                  (field & main::data_field_flag::CONSTANT ? "Constant" : "Data"),
                  (field & main::data_field_flag::VARIABLE ? "Variable" : "Array"),
                  (field & main::data_field_flag::RELATIVE ? "Relative" : "Absolute"));
        if (field & main::data_field_flag::WRAP)
        {
            std::formatter<string_view>::format(",Wrap", ctx);
        }
        if (field & main::data_field_flag::NONLINEAR)
        {
            std::formatter<string_view>::format(",Nonlinear", ctx);
        }
        if (field & main::data_field_flag::NO_PREFERRED)
        {
            std::formatter<string_view>::format(",NoPreferred", ctx);
        }
        if (field & main::data_field_flag::NULL_STATE)
        {
            std::formatter<string_view>::format(",NullState", ctx);
        }
        if (field & main::data_field_flag::VOLATILE)
        {
            std::formatter<string_view>::format(",Volatile", ctx);
        }
        if (field & main::data_field_flag::BUFFERED_BYTES)
        {
            std::formatter<string_view>::format(",BufferedBytes", ctx);
        }
        return ctx.out();
    }
};

/// @brief  Formatter specialization for HID collection types.
template <>
struct std::formatter<hid::rdf::main::collection_type> : public std::formatter<string_view>
{
  public:
    template <typename FormatContext>
    FormatContext::iterator format(const hid::rdf::main::collection_type& collection,
                                   FormatContext& ctx) const
    {
        using namespace hid::rdf;
        const char* name = nullptr;
        switch (collection)
        {
        case main::collection_type::PHYSICAL:
            name = "Physical";
            break;
        case main::collection_type::APPLICATION:
            name = "Application";
            break;
        case main::collection_type::LOGICAL:
            name = "Logical";
            break;
        case main::collection_type::REPORT:
            name = "Report";
            break;
        case main::collection_type::NAMED_ARRAY:
            name = "Named Array";
            break;
        case main::collection_type::USAGE_SWITCH:
            name = "Usage Switch";
            break;
        case main::collection_type::USAGE_MODIFIER:
            name = "Usage Modifier";
            break;
        default:
            break;
        }
        if (name)
        {
            return std::formatter<string_view>::format(name, ctx);
        }
        return format_to(ctx.out(), "Unknown({:#x})",
                         static_cast<std::underlying_type_t<main::collection_type>>(collection));
    }
};

/// @brief Formatter specialization for HID report descriptors.
/// @tparam TIterator: descriptor view iterator type (@ref reinterpret_iterator or @ref
/// copy_iterator)
template <typename TDescIterator>
struct std::formatter<hid::rdf::descriptor_view_base<TDescIterator>>
{
  private:
    unsigned width_{4};

  public:
    using descriptor_view_type = hid::rdf::descriptor_view_base<TDescIterator>;

    constexpr auto parse(std::format_parse_context& ctx)
    {
#if 0
        if ((ctx.begin() != ctx.end()) and
            (std::from_chars(ctx.begin(), ctx.end(), width_).ec != std::errc{}))
        {
            throw std::format_error("Invalid format specifier");
        }
#endif
        return ctx.begin();
    }

    template <typename FormatContext>
    FormatContext::iterator format(const descriptor_view_type& desc, FormatContext& ctx) const
    {
        using namespace hid::rdf;
        struct parsing_formatter : public hid::rdf::parser<TDescIterator>
        {
            using base = hid::rdf::parser<TDescIterator>;
            using item_type = base::item_type;
            using items_view_type = base::items_view_type;
            using control = base::control;
            using base::get_usage;

            FormatContext& ctx_;
            unsigned width_;
            unsigned collection_depth_{};

            parsing_formatter(const descriptor_view_type& desc_view, FormatContext& ctx,
                              unsigned width)
                : base(), ctx_(ctx), width_(width)
            {
                auto it = base::parse_items(desc_view);
                format_items(items_view_type{it, desc_view.end()});
            }

            void format_items(const items_view_type& main_section,
                              const global_item_store& global_state = {},
                              std::uint16_t main_data_field = 0)
            {
                auto fs_ = string("{}({})\n");
                fs_.insert(0, std::string(width_ * collection_depth_, ' '));

                for (const auto& item : main_section)
                {
                    auto value_signed = item.value_signed();
                    auto value_unsigned = item.value_unsigned();
                    hid::usage_t usage = hid::nullusage;
                    const char* value_fs{};
                    format_args args = make_format_args("Unknown", value_unsigned);

                    switch (item.type())
                    {
                    case hid::rdf::item_type::MAIN:
                        switch (item.main_tag())
                        {
                        case main::tag::INPUT:
                            args = make_format_args(
                                "Input", *((hid::rdf::main::field_type*)&main_data_field));
                            break;
                        case main::tag::OUTPUT:
                            args = make_format_args(
                                "Output", *((hid::rdf::main::field_type*)&main_data_field));
                            break;
                        case main::tag::FEATURE:
                            args = make_format_args(
                                "Feature", *((hid::rdf::main::field_type*)&main_data_field));
                            break;
                        case main::tag::COLLECTION:
                            args = make_format_args(
                                "Collection", *((hid::rdf::main::collection_type*)&value_unsigned));
                            break;
                        case main::tag::END_COLLECTION:
                            args = make_format_args("End Collection", "");
                            break;
                        default:
                            value_unsigned = std::bit_cast<uint8_t>((item_header)item);
                            value_fs = ":#04x";
                            break;
                        }
                        break;
                    case hid::rdf::item_type::GLOBAL:
                        switch (item.global_tag())
                        {
                        case global::tag::USAGE_PAGE:
                        {
                            auto info = hid::page::get_page_info(value_unsigned);
                            if (info.valid_page())
                            {
                                args = make_format_args("Usage Page", info.page_name);
                            }
                            else
                            {
                                value_fs = ":#06x";
                                args = make_format_args("Usage Page", value_unsigned);
                            }
                            break;
                        }
                        case global::tag::LOGICAL_MINIMUM:
                            args = make_format_args("Logical Minimum", value_signed);
                            break;
                        case global::tag::LOGICAL_MAXIMUM:
                            if (main_data_field & main::data_field_flag::VARIABLE)
                            {
                                args = make_format_args("Logical Maximum", value_signed);
                            }
                            else
                            {
                                args = make_format_args("Logical Maximum", value_unsigned);
                            }
                            break;
                        case global::tag::PHYSICAL_MINIMUM:
                            args = make_format_args("Physical Minimum", value_signed);
                            break;
                        case global::tag::PHYSICAL_MAXIMUM:
                            args = make_format_args("Physical Maximum", value_signed);
                            break;
                        case global::tag::UNIT_EXPONENT:
                            value_signed = unit::get_exponent(item);
                            args = make_format_args("Unit Exponent", value_signed);
                            break;
                        case global::tag::UNIT:
                            value_fs = ":#010x";
                            args = make_format_args("Unit", value_unsigned); // TODO
                            break;
                        case global::tag::REPORT_SIZE:
                            args = make_format_args("Report Size", value_unsigned);
                            break;
                        case global::tag::REPORT_ID:
                            args = make_format_args("Report ID", value_unsigned);
                            break;
                        case global::tag::REPORT_COUNT:
                            args = make_format_args("Report Count", value_unsigned);
                            break;
                        case global::tag::PUSH:
                            args = make_format_args("Push", "");
                            break;
                        case global::tag::POP:
                            args = make_format_args("Pop", "");
                            break;
                        default:
                            value_unsigned = std::bit_cast<uint8_t>((item_header)item);
                            value_fs = ":#04x";
                            break;
                        }
                        break;
                    case hid::rdf::item_type::LOCAL:
                        switch (item.local_tag())
                        {
                        case local::tag::USAGE:
                            usage = get_usage(item, global_state);
                            args = make_format_args("Usage", usage);
                            if (item.data_size() == 4)
                            {
                                value_fs = ":p";
                            }
                            break;
                        case local::tag::USAGE_MINIMUM:
                            usage = get_usage(item, global_state);
                            args = make_format_args("Usage Minimum", usage);
                            if (item.data_size() == 4)
                            {
                                value_fs = ":p";
                            }
                            break;
                        case local::tag::USAGE_MAXIMUM:
                            usage = get_usage(item, global_state);
                            args = make_format_args("Usage Maximum", usage);
                            if (item.data_size() == 4)
                            {
                                value_fs = ":p";
                            }
                            break;
                        case local::tag::DESIGNATOR_INDEX:
                            args = make_format_args("Designator Index", value_unsigned);
                            break;
                        case local::tag::DESIGNATOR_MINIMUM:
                            args = make_format_args("Designator Minimum", value_unsigned);
                            break;
                        case local::tag::DESIGNATOR_MAXIMUM:
                            args = make_format_args("Designator Maximum", value_unsigned);
                            break;
                        case local::tag::STRING_INDEX:
                            args = make_format_args("String Index", value_unsigned);
                            break;
                        case local::tag::STRING_MINIMUM:
                            args = make_format_args("String Minimum", value_unsigned);
                            break;
                        case local::tag::STRING_MAXIMUM:
                            args = make_format_args("String Maximum", value_unsigned);
                            break;
                        case local::tag::DELIMITER:
                            if (value_unsigned == 0)
                            {
                                args = make_format_args("Delimiter", "Open");
                            }
                            else if (value_unsigned == 1)
                            {
                                args = make_format_args("Delimiter", "Close");
                            }
                            else
                            {
                                args = make_format_args("Delimiter", value_unsigned);
                            }
                            break;
                        default:
                            value_unsigned = std::bit_cast<uint8_t>((item_header)item);
                            value_fs = ":#04x";
                            break;
                        }
                        break;
                    default:
                        value_unsigned = std::bit_cast<uint8_t>((item_header)item);
                        value_fs = ":#04x";
                        break;
                    }
                    auto* fs = &fs_;
                    if (value_fs)
                    {
                        auto fs2 = fs_;
                        fs = &fs2;
                        fs2.insert(fs2.find_last_of('{') + 1, value_fs);
                    }
                    vformat_to(ctx_.out(), *fs, args);
                }
            }

            control parse_collection_begin([[maybe_unused]] main::collection_type collection,
                                           const global_item_store& global_state,
                                           const items_view_type& main_section,
                                           [[maybe_unused]] unsigned tlc_count) override
            {
                // include the main item in the section as well
                const items_view_type section{main_section.begin(), ++main_section.end()};
                format_items(section, global_state);
                collection_depth_++;
                return control::CONTINUE;
            }
            control parse_collection_end(const global_item_store& global_state,
                                         const items_view_type& main_section,
                                         [[maybe_unused]] unsigned tlc_number) override
            {
                collection_depth_--;
                // include the main item in the section as well
                const items_view_type section{main_section.begin(), ++main_section.end()};
                format_items(section, global_state);
                return control::CONTINUE;
            }
            control parse_report_data_field([[maybe_unused]] const item_type& main_item,
                                            const global_item_store& global_state,
                                            const items_view_type& main_section,
                                            [[maybe_unused]] unsigned tlc_count) override
            {
                // include the main item in the section as well
                const items_view_type section{main_section.begin(), ++main_section.end()};
                format_items(section, global_state, main_item.value_unsigned());
                return control::CONTINUE;
            }
        };

        parsing_formatter formatter{desc, ctx, width_};
        return ctx.out();
    }
};

#endif // __HID_RDF_FORMATTER_HPP_
