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
#ifndef __HID_RDF_ITEM_H_
#define __HID_RDF_ITEM_H_

#include "constants.h"
#include "exception.h"

namespace hid::rdf
{
    /// \brief This class provides a view of an existing HID report descriptor item.
    ///        Items are variable in length, therefore are challenging to
    ///        consistently represent as a single type.
    class alignas(1) item
    {
    private:
        constexpr static byte_type LONG_ITEM_PREFIX = 0xfe;

        template<typename TTag>
        constexpr bool is_correct_type() const
        {
            return match_type<TTag>() == type();
        }

    public:
        using types = item_type;

        constexpr types type() const
        {
            return static_cast<types>((prefix_ >> 2) & 0x3);
        }

        /// \note Long item format is specified, but their use isn't.
        ///       It's highly recommended to reject HID report descriptors
        ///       as soon as a long item is encountered (is_type_valid() will evaluate to false).
        constexpr bool is_short() const
        {
#if (HID_RDF_LONG_ITEM_SUPPORT != 0)
            return prefix_ != LONG_ITEM_PREFIX;
#else
            return true;
#endif
        }

        constexpr bool is_type_valid() const
        {
            return type() != types::RESERVED;
        }

        /// \brief Get the item's tag, which can only be done once the item's type is known.
        /// \tparam TTag: HID item tag type
        /// \return The item's tag value
        template<typename TTag>
        constexpr TTag tag() const
        {
            HID_RDF_ASSERT(is_correct_type<TTag>(), ex_item_invalid_tag_type);
            if (is_short())
            {
                return static_cast<TTag>(prefix_ >> 4);
            }
            else
            {
                return static_cast<TTag>(*(&prefix_ + 2));
            }
        }

        constexpr byte_type data_size() const
        {
            if (is_short())
            {
                auto sizefield = prefix_ & 3;
                return (sizefield < 3) ? sizefield : 4;
            }
            else
            {
                return *(&prefix_ + 1);
            }
        }

        constexpr std::size_t size() const
        {
            if (is_short())
            {
                return sizeof(prefix_) + data_size();
            }
            else
            {
                return sizeof(prefix_) + 2 + data_size();
            }
        }

        constexpr bool has_data() const
        {
            return data_size() > 0;
        }

        constexpr const byte_type* data() const
        {
            if (is_short())
            {
                return (&prefix_ + 1);
            }
            else
            {
                return (&prefix_ + 3);
            }
        }

        constexpr std::uint32_t value_unsigned() const
        {
            HID_RDF_ASSERT(is_short(), ex_item_long);

            const byte_type* ptr = &prefix_ + 1;
            std::uint32_t value = 0;
            for (byte_type i = data_size(); i > 0;)
            {
                i--;
                value = (value << 8) | ptr[i];
            }
            return value;
        }

        constexpr std::int32_t value_signed() const
        {
            std::uint32_t uval = value_unsigned();
            std::int32_t value = static_cast<std::int32_t>(uval);
            const auto size = data_size();
            if ((size > 0) and (size < 4))
            {
                // sign extend
                auto shift = (8 * size) - 1;
                auto check = uval >> shift;
                if (check > 0)
                {
                    value |= 0xffffffff << shift;
                }
            }
            return value;
        }

        constexpr bool is_value_signed() const
        {
            auto sval = value_signed();
            return (sval & (1 << (8 * sizeof(sval) - 1))) != 0;
        }

        constexpr bool operator==(const item& rhs)
        {
            if (this->size() != rhs.size())
            {
                return false;
            }
            else
            {
                const byte_type* l = &this->prefix_;
                const byte_type* r = &rhs.prefix_;
                auto len = this->size();
                while (len--)
                {
                    if (*l++ != *r++)
                    {
                        return false;
                    }
                }
                return true;
            }
        }

        constexpr bool operator!=(const item& rhs)
        {
            return !(*this == rhs);
        }

    protected:
        constexpr item(byte_type prefix)
            : prefix_(prefix)
        {
        }
        constexpr item()
            : prefix_(LONG_ITEM_PREFIX)
        {
        }

        item(const item&) = default;
        item& operator=(const item&) = default;

    private:
        byte_type prefix_;
    };

    /// \brief This class is used to store a copy of an existing HID report descriptor short item.
    ///        Since reinterpret_cast<item*>(uint8_t*) isn't constexpr, copying is the next best
    ///        solution to be able to iterate through a descriptor in compile-time.
    class alignas(1) short_item_buffer : public item
    {
    public:
        constexpr short_item_buffer()
            : item(), buffer_()
        {
        }

        constexpr short_item_buffer(const byte_type* data)
            : item(data[0]), buffer_()
        {
            HID_RDF_ASSERT(is_short(), ex_item_long);

            for (std::size_t i = 0; i < data_size(); i++)
            {
                buffer_[i] = data[1 + i];
            }
        }

        short_item_buffer(const short_item_buffer&) = default;
        short_item_buffer& operator=(const short_item_buffer&) = default;

    private:
        byte_type buffer_[4];
    };

} // namespace hid::rdf

#endif // __HID_RDF_ITEM_H_
