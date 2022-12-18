#ifndef __HID_PAGE_RESERVED_POINT_OF_SALE_H_
#define __HID_PAGE_RESERVED_POINT_OF_SALE_H_

#include "hid/usage.h"

namespace hid::page
{
    class reserved_point_of_sale;
    template<>
    struct info<reserved_point_of_sale>
    {
        constexpr static usage_id_type base_id = 0x008f0000;
        constexpr static usage_id_type max_usage = 0x0000 | base_id;
        constexpr static const char* name = "Reserved Point of Sale";
    };
    class reserved_point_of_sale
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
        constexpr reserved_point_of_sale(usage_index_type value)
            : id((value & USAGE_INDEX_MASK) | info<reserved_point_of_sale>::base_id)
        {
        }
    private:
        usage_id_type id;
    };
}

#endif // __HID_PAGE_RESERVED_POINT_OF_SALE_H_

