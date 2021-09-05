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
#ifndef __HID_RDF_SHORT_ITEM_H_
#define __HID_RDF_SHORT_ITEM_H_

#include "item.h"

namespace hid
{
    namespace rdf
    {
        // byte array that concatenates with comma operator
        template<const std::size_t SIZE>
        class array : public std::array<byte_type, SIZE>
        {
        public:
            template<const std::size_t SIZE_2>
            constexpr array<SIZE + SIZE_2> operator , (array<SIZE_2> a2)
            {
                array<SIZE + SIZE_2> concat = { 0 };
                for (std::size_t i = 0; i < SIZE; i++)
                {
                    concat[i] = (*this)[i];
                }
                for (std::size_t i = 0; i < SIZE_2; i++)
                {
                    concat[SIZE + i] = a2[i];
                }
                return concat;
            }
        };

        // stores one HID report descriptor item
        template<const byte_type DATA_SIZE>
        class short_item : public array<1 + DATA_SIZE>
        {
            static_assert((DATA_SIZE <= 4) && (DATA_SIZE != 3));

            typedef typename array<1 + DATA_SIZE> base_t;

        public:
            template<typename TTag>
            constexpr short_item(TTag tag)
                : base_t({ static_cast<byte_type>((static_cast<byte_type>(tag) << 4) |
                    (static_cast<byte_type>(match_type<TTag>()) << 2) |
                    ((DATA_SIZE == 4) ? 3 : (DATA_SIZE & 3))) })
            {
                static_assert(match_type<TTag>() != item_type::RESERVED);
            }

            template<typename TTag, typename TData>
            constexpr short_item(TTag tag, TData data)
                : short_item(tag)
            {
                static_assert(std::is_integral<TData>::value);

                for (byte_type i = 0; i < DATA_SIZE; i++)
                {
                    (*this)[1 + i] = data;
                    data >>= 8;
                }
            }

            constexpr bool operator==(const item& rhs)
            {
                if (this->size() != rhs.size())
                {
                    return false;
                }
                else
                {
                    for (std::size_t i = 0; i < this->size(); i++)
                    {
                        if ((*this)[i] != rhs[i])
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
        };
    }
}

#endif // __HID_RDF_SHORT_ITEM_H_
