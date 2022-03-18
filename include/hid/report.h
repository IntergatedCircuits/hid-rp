/// \file
///
/// \author Benedek Kupper
/// \date   2022
///
/// \copyright
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
    enum class report_type : std::uint8_t
    {
        INPUT    = 0x01, // Report sent by the device
        OUTPUT   = 0x02, // Report sent to the device
        FEATURE  = 0x03, // Bidirectional configuration report
    };

    enum class protocol : std::uint8_t
    {
        REPORT     = 0x01, // Default HID protocol
        BOOT       = 0x00, // BOOT protocol (either keyboard or mouse, as specified in USB HID class document)
    };

    /// \brief A report is uniquely identified by two parameters: its type, and its (optional) ID
    class report_selector
    {
    public:
        constexpr report_selector(report_type type, std::uint8_t id = 0)
            : storage_((static_cast<std::uint16_t>(type) << 8) | id)
        {
        }
        constexpr report_selector()
        {
        }
        constexpr void clear()
        {
            *this = report_selector();
        }
        constexpr bool valid() const
        {
            return static_cast<std::uint8_t>(type()) > 0;
        }
        constexpr report_type type() const
        {
            return static_cast<report_type>(storage_ >> 8);
        }
        constexpr std::uint8_t id() const
        {
            return static_cast<std::uint8_t>(storage_);
        }
        constexpr friend bool operator ==(const report_selector &lhs, const report_selector& rhs)
        {
            return (lhs.storage_ == rhs.storage_);
        }
        constexpr friend bool operator !=(const report_selector &lhs, const report_selector& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        std::uint16_t storage_ = 0;
    };

    /// \brief Base type for report storage structures. Inherit from \ref report type instead!
    template<const report_type TYPE, const std::uint8_t REPORT_ID>
    struct report_base
    {
        std::uint8_t *data()
        {
            return reinterpret_cast<std::uint8_t*>(this);
        }
        const std::uint8_t *data() const
        {
            return reinterpret_cast<const std::uint8_t*>(this);
        }
        constexpr static report_type type()
        {
            return TYPE;
        }
        constexpr static std::uint8_t ID = REPORT_ID;
        constexpr static std::uint8_t id()
        {
            return REPORT_ID;
        }
        constexpr static report_selector selector()
        {
            return report_selector(type(), id());
        }
    };

    template<const report_type TYPE, const std::uint8_t REPORT_ID = 0, typename Enabled = void>
    struct report;

    template<const report_type TYPE, const std::uint8_t REPORT_ID>
    struct report<TYPE, REPORT_ID, std::enable_if_t<REPORT_ID == 0>> : public report_base<TYPE, REPORT_ID>
    {
        constexpr bool is_id_valid() const
        {
            return true;
        }
    };

    template<const report_type TYPE, const std::uint8_t REPORT_ID>
    struct report<TYPE, REPORT_ID, std::enable_if_t<(REPORT_ID > 0)>> : public report_base<TYPE, REPORT_ID>
    {
        std::uint8_t id_ = REPORT_ID;

        constexpr bool is_id_valid() const
        {
            return id_ == REPORT_ID;
        }
    };
}

#endif // __HID_REPORT_H_
