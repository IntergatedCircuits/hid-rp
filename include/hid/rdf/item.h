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

#include <cstdint>
#include <cstddef>
#include <cassert>

#include "constants.h"

namespace hid
{
    namespace rdf
    {
        template<const byte_type DATA_SIZE>
        class short_item;

        class alignas(1) item
        {
            template<const byte_type DATA_SIZE>
            friend class short_item;

        public:
            using types = item_type;

            // long item format is specified, but their use isn't
            constexpr bool is_short() const
            {
                //return prefix_ == 0xfe;
                return true;
            }

            constexpr types type() const
            {
                if (is_short())
                {
                    return static_cast<types>((prefix_ >> 2) & 0x3);
                }
                else
                {
                    return types::RESERVED;
                }
            }

        private:
            template<typename TTag>
            constexpr static types match_type()
            {
                if (std::integral_constant<bool, std::is_same<TTag, main::tag>::value>::value)
                {
                    return types::MAIN;
                }
                else if (std::integral_constant<bool, std::is_same<TTag, global::tag>::value>::value)
                {
                    return types::GLOBAL;
                }
                else if (std::integral_constant<bool, std::is_same<TTag, local::tag>::value>::value)
                {
                    return types::LOCAL;
                }
                else
                {
                    return types::RESERVED;
                }
            }

            template<typename TTag>
            constexpr bool is_correct_type() const
            {
                return match_type<TTag>() == type();
            }

        public:
            template<typename TTag, typename std::enable_if<
                std::is_same<TTag, main::tag>::value ||
                std::is_same<TTag, global::tag>::value ||
                std::is_same<TTag, local::tag>::value >::type* = nullptr>
                constexpr TTag tag() const
            {
                assert(is_correct_type<TTag>());
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
                assert(is_short());

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
                assert(is_short());

                std::uint32_t uval = value_unsigned();
                std::int32_t value = static_cast<std::int32_t>(uval);
                const auto size = data_size();
                if ((size > 0) && (size < 4))
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

        private:
            template<const std::size_t SIZE>
            constexpr item(const std::array<byte_type, SIZE>& data)
                : prefix_(data[0])
            {
                static_assert(SIZE > 0);
            }

            // non-copyable
            item(const item&) = delete;
            item& operator=(const item&) = delete;
            // non-movable
            item(const item&&) = delete;
            item& operator=(const item&&) = delete;

            byte_type prefix_;
        };
    }
}

#endif // __HID_RDF_ITEM_H_
