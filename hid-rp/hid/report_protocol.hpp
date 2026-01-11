/// @file
///
/// @author Benedek Kupper
/// @date   2022
///
/// @copyright
///         This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
///         If a copy of the MPL was not distributed with this file, You can obtain one at
///         https://mozilla.org/MPL/2.0/.
///
#ifndef __HID_RDF_REPORT_PROTOCOL_HPP_
#define __HID_RDF_REPORT_PROTOCOL_HPP_

#include <algorithm>
#include <array>
#include <ranges>
#include "hid/rdf/global_items.hpp"
#include "hid/rdf/parser.hpp"

namespace hid
{
struct report_protocol_properties
{
    using descriptor_view_type = rdf::ce_descriptor_view;
    using size_type = std::uint16_t;

    size_type max_input_size{};
    size_type max_output_size{};
    size_type max_feature_size{};
    report::id::type input_report_count{};
    report::id::type output_report_count{};
    report::id::type feature_report_count{};
    bool report_id_present{};

    constexpr bool operator==(const report_protocol_properties& other) const = default;
    constexpr bool operator!=(const report_protocol_properties& other) const = default;

    constexpr size_type max_report_size() const
    {
        return std::max(max_input_size, std::max(max_output_size, max_feature_size));
    }
    constexpr size_type max_report_size(report::type type) const
    {
        switch (type)
        {
        case report::type::INPUT:
            return max_input_size;
        case report::type::OUTPUT:
            return max_output_size;
        case report::type::FEATURE:
            return max_feature_size;
        default:
            return 0;
        }
    }

    constexpr size_type report_count() const
    {
        return input_report_count + output_report_count + feature_report_count;
    }
    constexpr report::id::type report_count(report::type type) const
    {
        switch (type)
        {
        case report::type::INPUT:
            return input_report_count;
        case report::type::OUTPUT:
            return output_report_count;
        case report::type::FEATURE:
            return feature_report_count;
        default:
            return 0;
        }
    }

    constexpr bool uses_report_ids() const { return report_id_present; }

    /// @brief Define the report protocol properties, with no report ID use.
    /// @param max_input_size: The size of the longest INPUT report in bytes, including the report
    /// ID (if used)
    /// @param max_output_size: The size of the longest OUTPUT report in bytes, including the report
    /// ID (if used)
    /// @param max_feature_size: The size of the longest FEATURE report in bytes, including the
    /// report ID (if used)
    constexpr explicit report_protocol_properties(size_type max_input_size,
                                                  size_type max_output_size,
                                                  size_type max_feature_size)
        : max_input_size(max_input_size),
          max_output_size(max_output_size),
          max_feature_size(max_feature_size),
          input_report_count(bool(max_input_size)),
          output_report_count(bool(max_output_size)),
          feature_report_count(bool(max_feature_size)),
          report_id_present(false)
    {}

    /// @brief Define the report protocol properties manually.
    /// @param max_input_size: The size of the longest INPUT report in bytes, including the report
    /// ID (if used)
    /// @param max_output_size: The size of the longest OUTPUT report in bytes, including the report
    /// ID (if used)
    /// @param max_feature_size: The size of the longest FEATURE report in bytes, including the
    /// report ID (if used)
    /// @param report_count: The number of distinct reports defined by the protocol
    /// @param input_report_count: The highest INPUT report ID used by the protocol
    /// @param output_report_count: The highest OUTPUT report ID used by the protocol
    /// @param feature_report_count: The highest FEATURE report ID used by the protocol
    /// @param report_id_present: Whether the protocol uses report IDs at all
    constexpr explicit report_protocol_properties(
        size_type max_input_size, size_type max_output_size, size_type max_feature_size,
        report::id::type input_report_count, report::id::type output_report_count,
        report::id::type feature_report_count, bool report_id_present = true)
        : max_input_size(max_input_size),
          max_output_size(max_output_size),
          max_feature_size(max_feature_size),
          input_report_count(input_report_count),
          output_report_count(output_report_count),
          feature_report_count(feature_report_count),
          report_id_present(report_id_present)
    {}

    /// @brief This class parses the HID report descriptor, gathering all report size
    ///        and TLC assignment information, and verifying that the descriptor describes
    ///        a valid HID protocol.
    template <typename TIterator = descriptor_view_type::iterator>
    class parser : public rdf::parser<TIterator>
    {
      public:
        using base = rdf::parser<TIterator>;
        using item_type = base::item_type;
        using items_view_type = base::items_view_type;
        using control = base::control;

        constexpr parser(const rdf::descriptor_view_base<TIterator>& desc_view)
            : base()
        {
            base::parse_items(desc_view);

            // when finished, run a final check that each report has byte size
            for (const auto& sizes : report_bit_sizes_)
            {
                for (const auto& size : sizes)
                {
                    HID_RP_ASSERT(size % 8 == 0, ex_report_total_size_invalid);
                }
            }
        }

        // https://stackoverflow.com/questions/72835571/constexpr-c-error-destructor-used-before-its-definition
        constexpr ~parser() override {}

        constexpr size_type max_report_size(report::type type) const
        {
            if (!uses_report_ids())
            {
                return bit_size(type, 0) / 8;
            }
            else
            {
                auto& report_sizes = bit_sizes_by_type(type);
                auto begin = report_sizes.begin();
                auto max_size = *std::max_element(++begin, report_sizes.end()) / 8u;
                if (max_size > 0)
                {
                    return sizeof(report::id) + max_size;
                }
                else
                {
                    return 0;
                }
            }
        }

        constexpr bool uses_report_ids() const { return max_report_id() > 0; }

        constexpr report::id::type max_report_id() const
        {
            return std::max(
                std::max(max_report_id(report::type::INPUT), max_report_id(report::type::OUTPUT)),
                max_report_id(report::type::FEATURE));
        }

        constexpr report::id::type max_report_id(report::type type) const
        {
            const auto& sizes = report_bit_sizes_[static_cast<std::size_t>(type) - 1];
            auto rit = std::ranges::find_if(sizes | std::views::reverse,
                                            [](size_type x) { return x != 0; });
            return rit == sizes.rend() ? 0 : std::distance(rit, sizes.rend()) - 1;
        }

        constexpr size_type report_count() const
        {
            return static_cast<size_type>(std::ranges::count_if(
                report_bit_sizes_ | std::views::join, [](auto v) { return v > 0; }));
        }
        constexpr report::id::type report_count(report::type type) const
        {
            const auto& sizes = report_bit_sizes_[static_cast<std::size_t>(type) - 1];
            return static_cast<report::id::type>(
                std::ranges::count_if(sizes, [](auto v) { return v > 0; }));
        }

        template <std::size_t N>
        constexpr void fill_report_selector_table(std::array<report::selector, N>& table) const
        {
            HID_RP_ASSERT(table.size() == report_count(), ex_report_table_invalid_size);
            auto table_it = table.begin();
            for (uint8_t type = 0; type < report_bit_sizes_.size(); ++type)
            {
                for (std::size_t id = 0; id < report_bit_sizes_.front().size(); ++id)
                {
                    if (report_bit_sizes_[type][id] > 0)
                    {
                        *table_it = report::selector(static_cast<report::type>(type + 1), id);
                        ++table_it;
                    }
                }
            }
        }

      private:
        using base::check_delimiters;
        using base::get_logical_limits_signed;
        using base::get_logical_limits_unsigned;
        using base::get_physical_limits;
        using base::get_report_data_field_params;
        using base::parse_items;

        constexpr control
        parse_collection_begin([[maybe_unused]] rdf::main::collection_type collection,
                               [[maybe_unused]] const rdf::global_item_store& global_state,
                               const items_view_type& main_section,
                               [[maybe_unused]] unsigned tlc_number) override
        {
            // only for descriptor verification purpose
            HID_RP_ASSERT(!check_delimiters(main_section) or
                              (collection != rdf::main::collection_type::APPLICATION),
                          ex_delimiter_invalid_location);
            return control::CONTINUE;
        }

        constexpr control
        parse_collection_end([[maybe_unused]] const rdf::global_item_store& global_state,
                             const items_view_type& main_section,
                             [[maybe_unused]] unsigned tlc_number) override
        {
            // only for descriptor verification purpose
            HID_RP_ASSERT(!check_delimiters(main_section), ex_delimiter_invalid_location);
            return control::CONTINUE;
        }

        constexpr control parse_report_data_field(
            const item_type& main_item, const rdf::global_item_store& global_state,
            [[maybe_unused]] const items_view_type& main_section, unsigned tlc_count) override
        {
            using namespace hid::rdf;
            report::type rtype = main::tag_to_report_type(main_item.main_tag());

            auto report_params = get_report_data_field_params(global_state);
            if (report_params.id)
            {
                // check that there is no report field with missing ID
                HID_RP_ASSERT(std::find_if(report_bit_sizes_.begin(), report_bit_sizes_.end(),
                                           [](auto sizes)
                                           { return sizes[0] > 0; }) == report_bit_sizes_.end(),
                              ex_report_id_missing);
            }

            if (main_item.value_unsigned() & main::data_field_flag::BUFFERED_BYTES)
            {
                HID_RP_ASSERT((report_params.size % 8 == 0) and
                                  (bit_size(rtype, report_params.id) % 8 == 0),
                              ex_buffered_bytes_misaligned, main_item.main_tag());
            }

            // increase size of this report
            bit_size(rtype, report_params.id) += report_params.size * report_params.count;

            // the following are only compile-time checks:
            // verify that the report doesn't cross TLC boundary
            auto& report_tlc_index = tlc_index(rtype, report_params.id);
            if (report_tlc_index == 0)
            {
                // first piece of the report, assign to TLC now
                report_tlc_index = tlc_count;
            }
            else
            {
                HID_RP_ASSERT(report_tlc_index == tlc_count, ex_report_crossing_tlc_bounds);
            }

            HID_RP_ASSERT(!check_delimiters(main_section) or
                              (main_item.value_unsigned() & main::data_field_flag::VARIABLE),
                          ex_delimiter_invalid_main_item);

            // usage limits verification
            short_item_buffer usage_min_item{};
            short_item_buffer usage_max_item{};
            bool usage_present = false;
            for (const item_type& item : main_section)
            {
                switch (item.unified_tag())
                {
                case tag::USAGE_MINIMUM:
                    HID_RP_ASSERT(!usage_min_item, ex_usage_min_duplicate);
                    usage_min_item = item;
                    break;
                case tag::USAGE_MAXIMUM:
                    HID_RP_ASSERT(!usage_max_item, ex_usage_max_duplicate);
                    usage_max_item = item;
                    break;
                case tag::USAGE:
                    usage_present = true;
                    break;
                default:
                    break;
                }
            }
            if (usage_min_item and usage_max_item)
            {
                if ((usage_min_item.data_size() == 4) or (usage_max_item.data_size() == 4))
                {
                    HID_RP_ASSERT(usage_min_item.data_size() == usage_max_item.data_size(),
                                  ex_usage_limits_size_mismatch);
                }
                auto usage_min = usage_min_item.value_unsigned();
                auto usage_max = usage_max_item.value_unsigned();
                HID_RP_ASSERT((usage_min >> 16) == (usage_max >> 16),
                              ex_usage_limits_page_mismatch);
                HID_RP_ASSERT(usage_min <= usage_max, ex_usage_limits_crossed);
                usage_present = true;
            }
            else
            {
                HID_RP_ASSERT(usage_min_item == usage_max_item, ex_usage_limit_missing);
            }

            if (!usage_present)
            {
                // skip limits verification on padding bits
            }
            else if ((main_item.value_unsigned() &
                      (main::data_field_flag::VARIABLE | main::data_field_flag::BUFFERED_BYTES)) ==
                     main::data_field_flag::VARIABLE)
            {
                auto logical_limits = get_logical_limits_signed(global_state);
                if (report_params.size < 32)
                {
                    HID_RP_ASSERT(logical_limits.min >=
                                      -(1 << std::int32_t(report_params.size - 1)),
                                  ex_logical_min_oob);
                    HID_RP_ASSERT(logical_limits.max <=
                                      (1 << std::int32_t(report_params.size /*- 1*/)),
                                  ex_logical_max_oob);
                }
                else
                {
                    HID_RP_ASSERT(logical_limits.min >= std::numeric_limits<std::int32_t>::min(),
                                  ex_logical_min_oob);
                    HID_RP_ASSERT(logical_limits.max <= std::numeric_limits<std::int32_t>::max(),
                                  ex_logical_max_oob);
                }

                get_physical_limits(global_state);
            }
            else
            {
                auto logical_limits = get_logical_limits_unsigned(global_state);
                HID_RP_ASSERT(logical_limits.min <= 1, ex_logical_min_oob);
                HID_RP_ASSERT(logical_limits.max <= (std::uint32_t(1) << report_params.size),
                              ex_logical_max_oob);

                get_physical_limits(global_state);
            }

            return control::CONTINUE;
        }

        constexpr size_type& bit_size(report::type rt, report::id::type id)
        {
            return bit_sizes_by_type(rt)[id];
        }
        constexpr const size_type& bit_size(report::type rt, report::id::type id) const
        {
            return bit_sizes_by_type(rt)[id];
        }
        constexpr std::array<size_type, report::id::max()>& bit_sizes_by_type(report::type rt)
        {
            return report_bit_sizes_[static_cast<report::id::type>(rt) - 1];
        }
        constexpr const std::array<size_type, report::id::max()>&
        bit_sizes_by_type(report::type rt) const
        {
            return report_bit_sizes_[static_cast<report::id::type>(rt) - 1];
        }

        constexpr unsigned& tlc_index(report::type rt, report::id::type id)
        {
            return tlc_indexes_by_type(rt)[id];
        }
        constexpr const unsigned& tlc_index(report::type rt, report::id::type id) const
        {
            return tlc_indexes_by_type(rt)[id];
        }
        constexpr std::array<unsigned, report::id::max()>& tlc_indexes_by_type(report::type rt)
        {
            return report_tlc_indexes_[static_cast<report::id::type>(rt) - 1];
        }
        constexpr const std::array<unsigned, report::id::max()>&
        tlc_indexes_by_type(report::type rt) const
        {
            return report_tlc_indexes_[static_cast<report::id::type>(rt) - 1];
        }

        std::array<std::array<size_type, report::id::max()>, 3> report_bit_sizes_{};
        std::array<std::array<unsigned, report::id::max()>, 3> report_tlc_indexes_{};
    };

    consteval explicit report_protocol_properties(const parser<>& parsed)
        : report_protocol_properties(
              parsed.max_report_size(report::type::INPUT),
              parsed.max_report_size(report::type::OUTPUT),
              parsed.max_report_size(report::type::FEATURE),
              parsed.report_count(report::type::INPUT), parsed.report_count(report::type::OUTPUT),
              parsed.report_count(report::type::FEATURE), parsed.uses_report_ids())
    {}

    /// @brief Define the report protocol properties by parsing the descriptor in compile-time.
    /// @param desc_view: View of the HID report descriptor
    consteval explicit report_protocol_properties(const descriptor_view_type& desc_view)
        : report_protocol_properties(parser<>(desc_view))
    {}
};

/// @brief This class holds the necessary information about the specific HID report protocol
///        that the device implements. This information is used by the transport layer
///        to establish a proper size data channel between the host and the device.
///        This class can gather all parameters from the HID report descriptor at compile-time,
///        and also performs verification of the descriptor (compiler error when the descriptor is
///        faulty).
struct report_protocol : public report_protocol_properties
{
    descriptor_view_type descriptor;

    /// @brief Define the report protocol manually.
    /// @param desc_view: View of the HID report descriptor
    /// @param args: Arguments for report_protocol_properties constructor
    template <typename... TArgs>
    constexpr explicit report_protocol(const descriptor_view_type& desc_view, TArgs&&... args)
        : report_protocol_properties(std::forward<TArgs>(args)...), descriptor(desc_view)
    {}

    /// @brief Define the report protocol by parsing the descriptor in compile-time.
    /// @param desc_view: View of the HID report descriptor
    consteval explicit report_protocol(const descriptor_view_type& desc_view)
        : report_protocol_properties(desc_view), descriptor(desc_view)
    {}

    /// @brief  This method constructs a @ref hid::report_protocol object from a rvalue
    ///         descriptor, producing a static lvalue of it in the process.
    /// @tparam Data: the descriptor array, acquired e.g. from a @ref hid::rdf::descriptor call
    template <auto Data>
    static consteval auto from_descriptor()
    {
        return report_protocol(descriptor_view_type::from_descriptor<Data>());
    }
};

/// @brief  Create a table that contains all report selectors defined by the report descriptor,
///         for correctly sizing and filling GATT HID attributes.
/// @tparam Data: the descriptor array, acquired e.g. from a @ref hid::rdf::descriptor call
/// @return a std::array<hid::report::selector, N> table listing the report selectors used by the
///         report descriptor
template <auto Data>
inline consteval auto make_report_selector_table()
{
    constexpr report_protocol::parser<> parser{rdf::ce_descriptor_view::from_descriptor<Data>()};
    std::array<report::selector, parser.report_count()> table;
    parser.fill_report_selector_table(table);
    return table;
}

} // namespace hid

#endif // __HID_RDF_REPORT_PROTOCOL_HPP_
