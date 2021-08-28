/// \file
///
/// \author Benedek Kupper
/// \date   2021
///
/// \copyright
///         This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
///         If a copy of the MPL was not distributed with this file, You can obtain one at
///         https://mozilla.org/MPL/2.0/.
///
#ifndef __HID_RDF_MAIN_ITEMS_H_
#define __HID_RDF_MAIN_ITEMS_H_

#include "short_item.h"

namespace hid
{
    namespace rdf
    {
        namespace main // internal use
        {
            class collection_begin_item : public short_item<1>
            {
            public:
                constexpr collection_begin_item(collection_type t)
                    : short_item(main::tag::COLLECTION, static_cast<byte_type>(t))
                {
                }
            };

            class collection_end_item : public short_item<0>
            {
            public:
                constexpr collection_end_item()
                    : short_item(main::tag::END_COLLECTION)
                {
                }
            };
        }

        namespace collection
        {
            using type = main::collection_type;

            template <std::size_t... sz>
            constexpr auto application(array<sz>... items)
            {
                return main::collection_begin_item(type::APPLICATION), (items, ...), main::collection_end_item();
            }

            template <std::size_t... sz>
            constexpr auto logical(std::array<byte_type, sz>... items)
            {
                return main::collection_begin_item(type::LOGICAL), (items, ...), main::collection_end_item();
            }

            template <std::size_t... sz>
            constexpr auto report(std::array<byte_type, sz>... items)
            {
                return main::collection_begin_item(type::REPORT), (items, ...), main::collection_end_item();
            }

            template <std::size_t... sz>
            constexpr auto named_array(std::array<byte_type, sz>... items)
            {
                return main::collection_begin_item(type::NAMED_ARRAY), (items, ...), main::collection_end_item();
            }

            template <std::size_t... sz>
            constexpr auto physical(std::array<byte_type, sz>... items)
            {
                return main::collection_begin_item(type::PHYSICAL), (items, ...), main::collection_end_item();
            }

            template <std::size_t... sz>
            constexpr auto usage_modifier(std::array<byte_type, sz>... items)
            {
                return main::collection_begin_item(type::USAGE_MODIFIER), (items, ...), main::collection_end_item();
            }

            template <std::size_t... sz>
            constexpr auto usage_switch(std::array<byte_type, sz>... items)
            {
                return main::collection_begin_item(type::USAGE_SWITCH), (items, ...), main::collection_end_item();
            }
        }

        namespace main // internal use
        {
            // the combinations are simplified to a subset that makes sense
            enum field_type : std::uint16_t
            {
                ARRAY                = data_field_flag::ARRAY,
                BUFFERED_VARIABLE    = data_field_flag::VARIABLE | data_field_flag::BUFFERED_BYTES,
                ABSOLUTE_VARIABLE    = data_field_flag::VARIABLE | data_field_flag::ABSOLUTE,
                RELATIVE_VARIABLE    = data_field_flag::VARIABLE | data_field_flag::RELATIVE,
                ABSOLUTE_CONSTANT    = data_field_flag::CONSTANT | data_field_flag::VARIABLE | data_field_flag::ABSOLUTE,
                RELATIVE_CONSTANT    = data_field_flag::CONSTANT | data_field_flag::VARIABLE | data_field_flag::RELATIVE,
                PADDING              = data_field_flag::CONSTANT | data_field_flag::ARRAY,
            };

            // additional flags that can be set beyond the base type
            enum field_flags : std::uint16_t
            {
                NONE            = 0,
                WRAP            = data_field_flag::WRAP,
                NONLINEAR       = data_field_flag::NONLINEAR,
                NO_PREFERRED    = data_field_flag::NO_PREFERRED,
                NULL_STATE      = data_field_flag::NULL_STATE,
                VOLATILE        = data_field_flag::VOLATILE,
            };

            template<const byte_type DATA_SIZE>
            class data_field_item : public short_item<DATA_SIZE>
            {
            public:
                constexpr data_field_item(main::tag tag, std::uint16_t flags)
                    : short_item(tag, flags)
                {
                }
            };

            template<const main::tag TAG_>
            class data_field
            {
                constexpr static const main::tag TAG = TAG_;

            public:
                using flags = field_flags;
                using type = field_type;

                constexpr static auto array()
                {
                    return data_field_item<0>(TAG, field_type::ARRAY);
                }

                constexpr static auto buffered_variable()
                {
                    return data_field_item<2>(TAG, field_type::BUFFERED_VARIABLE);
                }

                constexpr static auto absolute_variable(flags extra_flags = flags::NONE)
                {
                    return data_field_item<1>(TAG, static_cast<std::uint16_t>(extra_flags) | field_type::ABSOLUTE_VARIABLE);
                }

                constexpr static auto relative_variable(flags extra_flags = flags::NONE)
                {
                    return data_field_item<1>(TAG, static_cast<std::uint16_t>(extra_flags) | field_type::RELATIVE_VARIABLE);
                }

                constexpr static auto absolute_constant(flags extra_flags = flags::NONE)
                {
                    return data_field_item<1>(TAG, static_cast<std::uint16_t>(extra_flags) | field_type::ABSOLUTE_CONSTANT);
                }

                constexpr static auto relative_constant(flags extra_flags = flags::NONE)
                {
                    return data_field_item<1>(TAG, static_cast<std::uint16_t>(extra_flags) | field_type::RELATIVE_CONSTANT);
                }

                constexpr static auto padding(byte_type bitsize)
                {
                    return report_count<1>(1), report_size<1>(bitsize), data_field_item<1>(TAG, field_type::PADDING);
                }
            };
        }

        using input        = main::data_field<main::tag::INPUT>;

        using output    = main::data_field<main::tag::OUTPUT>;

        using feature    = main::data_field<main::tag::FEATURE>;
    }
}

#endif // __HID_RDF_MAIN_ITEMS_H_