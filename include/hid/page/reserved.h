#ifndef __HID_PAGE_RESERVED_H_
#define __HID_PAGE_RESERVED_H_

#include "hid/usage.h"

namespace hid::page
{
    class reserved;
    template<>
    struct info<reserved>
    {
        constexpr static usage_id_type base_id = 0x00830000;
        constexpr static usage_id_type max_usage = 0x0000 | base_id;
        constexpr static const char* name = "Monitor Reserved";
    };
    class reserved
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
        constexpr reserved(usage_index_type value)
            : id((value & USAGE_INDEX_MASK) | info<reserved>::base_id)
        {
        }
    private:
        usage_id_type id;
    };
}

#endif // __HID_PAGE_RESERVED_H_

