#ifndef __HID_PAGE_MONITOR_H_
#define __HID_PAGE_MONITOR_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class monitor : usage_id_type;
    template<>
    struct info<monitor>
    {
        constexpr static usage_id_type base_id = 0x00800000;
        constexpr static usage_id_type max_usage = 0x0001 | base_id;
        constexpr static const char* name = "Monitor";
    };
    enum class monitor : usage_id_type
    {
        MONITOR_CONTROL = 0x0001 | info<monitor>::base_id,
    };
}

#endif // __HID_PAGE_MONITOR_H_

