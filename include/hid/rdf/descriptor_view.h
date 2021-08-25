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
#ifndef __HID_RDF_DESCRIPTOR_VIEW_H_
#define __HID_RDF_DESCRIPTOR_VIEW_H_

#include <iterator>

#include "item.h"

namespace hid
{
    namespace rdf
    {
        class descriptor_view
        {
        public:
            using value_type      = item;
            using const_pointer   = const value_type*;
            using const_reference = const value_type&;
            using pointer         = const value_type*;
            using reference       = const value_type&;

            constexpr descriptor_view()
                : _begin(nullptr), _end(nullptr)
            {
            }
            constexpr descriptor_view(const byte_type *data, std::size_t size)
                : _begin((pointer)data), _end((pointer)(data + size))
            {
            }
            template<const std::size_t SIZE>
            constexpr descriptor_view(const std::array<byte_type, SIZE>& arr)
                : _begin((pointer)arr.data()), _end((pointer)(arr.data() + arr.size()))
            {
            }
            template <typename TIterator>
            constexpr descriptor_view(const TIterator begin, const TIterator end)
                : _begin(std::addressof(*begin)),
                _end(std::addressof(*begin) + std::distance(begin, end))
            {
            }

            class iterator
            {
            public:
                using iterator_category = std::forward_iterator_tag;

                constexpr iterator(pointer ptr)
                    : _ptr(ptr)
                {
                }
                constexpr iterator(const iterator& other)
                    : _ptr(other._ptr)
                {
                }
                constexpr iterator& operator =(const iterator& other)
                {
                    _ptr = other._ptr;
                    return *this;
                }
                constexpr iterator operator++()
                {
                    iterator i = *this;
                    _ptr += i->size();
                    return i;
                }
                constexpr iterator operator++(int)
                {
                    iterator retval = *this;
                    ++(*this);
                    return retval;
                }
                constexpr reference operator*()
                {
                    return *_ptr;
                }
                constexpr pointer operator->()
                {
                    return _ptr;
                }
                constexpr bool operator==(const iterator& rhs) const
                {
                    return _ptr == rhs._ptr;
                }
                constexpr bool operator!=(const iterator& rhs) const
                {
                    return _ptr != rhs._ptr;
                }

            private:
                pointer _ptr;
            };

            using const_iterator = const iterator;

            pointer data()
            {
                return _begin;
            }
            const_pointer data() const
            {
                return _begin;
            }
            std::size_t size() const
            {
                return std::distance(_begin, _end);
            }
            iterator begin()
            {
                return _begin;
            }
            const_iterator begin() const
            {
                return _begin;
            }
            iterator end()
            {
                return _end;
            }
            const_iterator end() const
            {
                return _end;
            }

        private:
            pointer _begin;
            pointer _end;
        };
    }
}

#endif // __HID_RDF_DESCRIPTOR_VIEW_H_
