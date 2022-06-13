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
#ifndef __HID_REPORT_H_
#define __HID_REPORT_H_

#include <cstdint>
#include <type_traits>

namespace hid
{
    enum class protocol : std::uint8_t
    {
        REPORT     = 0x01, // Default HID protocol
        BOOT       = 0x00, // BOOT protocol (either keyboard or mouse, as specified in USB HID class document)
    };

    namespace report
    {
        enum class type : std::uint8_t
        {
            INPUT    = 0x01, // Report sent by the device
            OUTPUT   = 0x02, // Report sent to the device
            FEATURE  = 0x03, // Bidirectional configuration report
        };

        /// @note  An HID report descriptor either doesn't define report IDs at all,
        ///        or uses report IDs starting from index 1.
        ///        When report IDs are used, they are always the first byte of any HID report.
        class id
        {
        public:
            using type = std::uint8_t;

            constexpr id(type value)
                : value_(value)
            {
            }
            constexpr static type min()
            {
                return 1;
            }
            constexpr static type max()
            {
                return std::numeric_limits<type>::max();
            }
            constexpr operator type&()
            {
                return value_;
            }
            constexpr operator type() const
            {
                return value_;
            }
            constexpr bool valid() const
            {
                return value_ >= min();
            }
            constexpr friend bool operator ==(const id &lhs, const id& rhs)
            {
                return (lhs.value_ == rhs.value_);
            }
            constexpr friend bool operator !=(const id &lhs, const id& rhs)
            {
                return !(lhs == rhs);
            }
            constexpr friend bool operator ==(const id &lhs, const id::type& rhs)
            {
                return (lhs.value_ == rhs);
            }
            constexpr friend bool operator !=(const id &lhs, const id::type& rhs)
            {
                return !(lhs == rhs);
            }

        private:
            type value_;
        };

        /// @brief A report is uniquely identified by two parameters: its type, and its (optional) ID
        class selector
        {
        public:
            constexpr selector(report::type t, report::id i = 0)
                : storage_((static_cast<std::uint16_t>(t) << 8) | static_cast<std::uint16_t>(i))
            {
            }
            constexpr selector()
            {
            }
            constexpr void clear()
            {
                *this = selector();
            }
            constexpr bool valid() const
            {
                return static_cast<std::uint8_t>(this->type()) > 0;
            }
            constexpr report::type type() const
            {
                return static_cast<report::type>(storage_ >> 8);
            }
            constexpr report::id id() const
            {
                return report::id(storage_);
            }
            constexpr friend bool operator ==(const selector &lhs, const selector& rhs)
            {
                return (lhs.storage_ == rhs.storage_);
            }
            constexpr friend bool operator !=(const selector &lhs, const selector& rhs)
            {
                return !(lhs == rhs);
            }

        private:
            std::uint16_t storage_ = 0;
        };

        /// @brief Base type for report storage structures. Inherit from @ref base type instead!
        template<report::type TYPE, id::type REPORT_ID>
        struct base_data
        {
            std::uint8_t *data()
            {
                return reinterpret_cast<std::uint8_t*>(this);
            }
            const std::uint8_t *data() const
            {
                return reinterpret_cast<const std::uint8_t*>(this);
            }
            constexpr static report::type type()
            {
                return TYPE;
            }
            constexpr static report::id::type ID = REPORT_ID;
            constexpr static report::id id()
            {
                return report::id(ID);
            }
            constexpr static report::selector selector()
            {
                return report::selector(type(), id());
            }
        };

        template<type TYPE, id::type REPORT_ID = 0, typename Enabled = void>
        struct base;

        template<type TYPE, id::type REPORT_ID>
        struct base<TYPE, REPORT_ID, std::enable_if_t<REPORT_ID == 0>> : public base_data<TYPE, REPORT_ID>
        {
        };

        template<type TYPE, id::type REPORT_ID>
        struct base<TYPE, REPORT_ID, std::enable_if_t<(REPORT_ID > 0)>> : public base_data<TYPE, REPORT_ID>
        {
            id id_ { REPORT_ID };
        };
    }
}

#endif // __HID_REPORT_H_
