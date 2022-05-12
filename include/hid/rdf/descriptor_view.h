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
#ifndef __HID_RDF_DESCRIPTOR_VIEW_H_
#define __HID_RDF_DESCRIPTOR_VIEW_H_

#include <iterator>

#include "item.h"

namespace hid::rdf
{
    /// @brief HID report descriptor iterator, which casts the underlying raw data to an item.
    class reinterpret_iterator
    {
    public:
        using value_type      = item;
        using const_pointer   = const value_type*;
        using const_reference = const value_type&;
        using pointer         = const value_type*;
        using reference       = const value_type&;

        using iterator_category = std::forward_iterator_tag;

        reinterpret_iterator(const byte_type* data)
            : ptr_(reinterpret_cast<pointer>(data))
        {
        }
        constexpr reinterpret_iterator(pointer ptr)
            : ptr_(ptr)
        {
        }
        constexpr reinterpret_iterator operator++()
        {
            reinterpret_iterator i = *this;
            ptr_ += i->size();
            return i;
        }
        constexpr reinterpret_iterator operator++(int)
        {
            reinterpret_iterator retval = *this;
            ++(*this);
            return retval;
        }
        constexpr reference operator*()
        {
            return *ptr_;
        }
        constexpr pointer operator->()
        {
            return ptr_;
        }
        constexpr bool operator==(const reinterpret_iterator& rhs) const
        {
            return ptr_ == rhs.ptr_;
        }
        constexpr bool operator!=(const reinterpret_iterator& rhs) const
        {
            return ptr_ != rhs.ptr_;
        }

    private:
        pointer ptr_;
    };

    /// @brief HID report descriptor iterator, which copies the actual short (!) item
    ///        into an internal buffer.
    class copy_iterator
    {
    public:
        using value_type      = item;
        using const_pointer   = const value_type*;
        using const_reference = const value_type&;
        using pointer         = const value_type*;
        using reference       = const value_type&;

        using iterator_category = std::forward_iterator_tag;

        constexpr copy_iterator(const byte_type* data)
            : ptr_(data)
        {
        }
        copy_iterator(pointer ptr)
            : ptr_(reinterpret_cast<decltype(ptr_)>(ptr))
        {
        }
        constexpr copy_iterator operator++()
        {
            copy_iterator i = *this;
            ptr_ += i->size();
            return i;
        }
        constexpr copy_iterator operator++(int)
        {
            copy_iterator retval = *this;
            ++(*this);
            return retval;
        }
        constexpr reference operator*()
        {
            return copy();
        }
        constexpr pointer operator->()
        {
            return &copy();
        }
        constexpr bool operator==(const copy_iterator& rhs) const
        {
            return ptr_ == rhs.ptr_;
        }
        constexpr bool operator!=(const copy_iterator& rhs) const
        {
            return ptr_ != rhs.ptr_;
        }

    private:
        constexpr reference copy()
        {
            copy_ = decltype(copy_)(ptr_);
            return copy_;
        }
        const byte_type *ptr_;
        short_item_buffer copy_;
    };

    template<typename TIterator>
    class descriptor_view_base
    {
    public:
        using value_type      = item;
        using const_pointer   = const value_type*;
        using const_reference = const value_type&;
        using pointer         = const value_type*;
        using reference       = const value_type&;
        using iterator        = TIterator;
        using const_iterator  = const iterator;

        constexpr descriptor_view_base()
            : begin_(nullptr), end_(nullptr)
        {
        }
        constexpr descriptor_view_base(const byte_type *data, std::size_t size)
            : begin_(data), end_(data + size)
        {
        }
        template<typename TArray>
        constexpr descriptor_view_base(const TArray& arr)
            : begin_(arr.data())
            , end_(arr.data() + arr.size())
        {
        }
        template <typename TIter>
        constexpr descriptor_view_base(const TIter begin, const TIter end)
            : begin_(std::addressof(*begin)),
            end_(std::addressof(*begin) + std::distance(begin, end))
        {
        }

        constexpr const byte_type* data() const
        {
            return begin_;
        }
        constexpr std::size_t size() const
        {
            return std::distance(begin_, end_);
        }
        constexpr iterator begin()
        {
            return begin_;
        }
        constexpr const_iterator begin() const
        {
            return begin_;
        }
        constexpr iterator end()
        {
            return end_;
        }
        constexpr const_iterator end() const
        {
            return end_;
        }

    private:
        const byte_type* begin_;
        const byte_type* end_;
    };

    /// @brief HID report descriptor view, use for runtime descriptor parsing.
    using descriptor_view = descriptor_view_base<reinterpret_iterator>;

    /// @brief HID report descriptor view, use for compile-time descriptor parsing.
    ///        It needs to copy each item to buffer, not the optimal solution for runtime.
    using ce_descriptor_view = descriptor_view_base<copy_iterator>;

} // namespace hid::rdf

#endif // __HID_RDF_DESCRIPTOR_VIEW_H_
