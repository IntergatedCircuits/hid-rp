#ifndef __HID_PAGE_ORDINAL_H_
#define __HID_PAGE_ORDINAL_H_

#include "hid/usage.h"

namespace hid::page
{
    class ordinal;
    template<>
    struct info<ordinal>
    {
        constexpr static usage_id_type base_id = 0x000a0000;
        constexpr static usage_id_type max_usage = 0x00ff | base_id;
        constexpr static const char* name = "Ordinal";
    };
    class ordinal
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
        constexpr ordinal(usage_index_type value)
            : id((value & USAGE_INDEX_MASK) | info<ordinal>::base_id)
        {
        }
    private:
        usage_id_type id;
    };
}

#endif // __HID_PAGE_ORDINAL_H_

