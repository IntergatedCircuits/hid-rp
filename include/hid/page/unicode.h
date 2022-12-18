#ifndef __HID_PAGE_UNICODE_H_
#define __HID_PAGE_UNICODE_H_

#include "hid/usage.h"

namespace hid::page
{
    class unicode;
    template<>
    struct info<unicode>
    {
        constexpr static usage_id_type base_id = 0x00100000;
        constexpr static usage_id_type max_usage = 0x0000 | base_id;
        constexpr static const char* name = "Unicode";
    };
    class unicode
    {
    public:
        constexpr operator usage_id_type&()
        {
            return id;
        }
        constexpr operator usage_id_type() const
        {
            return id;
        }
        constexpr unicode(usage_index_type value)
            : id((value & USAGE_INDEX_MASK) | info<unicode>::base_id)
        {
        }
    private:
        usage_id_type id;
    };
}

#endif // __HID_PAGE_UNICODE_H_

