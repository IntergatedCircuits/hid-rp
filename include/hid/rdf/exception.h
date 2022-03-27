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
#ifndef __HID_RDF_EXCEPTION_H_
#define __HID_RDF_EXCEPTION_H_

#include "constants.h"

#ifndef HID_RDF_ASSERT
#define HID_RDF_ASSERT(CONDITION, EXCEPTION)   {if (!(CONDITION)) { throw (EXCEPTION()); }}
#endif

namespace hid::rdf
{
    class exception
    {
    public:
        using string_type = const char*;

        string_type what() const
        {
            return name_;
        }

    protected:
        constexpr exception(string_type name)
            : name_(name)
        {
        }

    private:
        string_type const name_;
    };

    struct ex_item_invalid_tag_type : public exception
    {
        constexpr ex_item_invalid_tag_type()
            : exception("invalid item tag type")
        {
        }
    };

    struct ex_item_long : public exception
    {
        constexpr ex_item_long()
            : exception("unexpected long item")
        {
        }
    };

    class parser_exception : public exception
    {
    public:
        using code_type = std::uint16_t;

    protected:
        template<typename TTag, typename TSubcode>
        constexpr parser_exception(string_type name, TTag tag, TSubcode subcode)
            : parser_exception(name, static_cast<code_type>(subcode),
                static_cast<code_type>(tag), static_cast<code_type>(match_type<TTag>()))
        {
            static_assert(match_type<TTag>() != item_type::RESERVED);
        }

        constexpr parser_exception(string_type name, code_type subcode)
            : parser_exception(name, subcode, 0, 0)
        {
        }

    private:
        code_type const code_;

        static constexpr code_type ERROR_FLAG = 1 << 15;
        static constexpr code_type VENDOR_DEFINED_FLAG = 1 << 14;

        constexpr parser_exception(string_type name, code_type subcode, code_type tag, code_type tag_type)
            : exception(name), code_(ERROR_FLAG | ((static_cast<code_type>(subcode) & 0xcf) << 8) |
                (static_cast<code_type>(tag) << 4) | (static_cast<code_type>(tag_type) << 2))
        {
        }
    };

    struct ex_report_id_zero : public parser_exception
    {
        constexpr ex_report_id_zero()
            : parser_exception("report ID is zero", global::tag::REPORT_ID, 0)
        {
        }
    };

} // namespace hid::rdf

#endif // __HID_RDF_EXCEPTION_H_
