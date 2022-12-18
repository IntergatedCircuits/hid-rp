#ifndef __HID_PAGE_MONITOR_ENUMERATED_VALUES_H_
#define __HID_PAGE_MONITOR_ENUMERATED_VALUES_H_

#include "hid/usage.h"

namespace hid::page
{
    class monitor_enumerated_values;
    template<>
    struct info<monitor_enumerated_values>
    {
        constexpr static usage_id_type base_id = 0x00810000;
        constexpr static usage_id_type max_usage = 0x00ff | base_id;
        constexpr static const char* name = "Monitor Enumerated Values";
    };
    class monitor_enumerated_values
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
        constexpr monitor_enumerated_values(usage_index_type value)
            : id((value & USAGE_INDEX_MASK) | info<monitor_enumerated_values>::base_id)
        {
        }
    private:
        usage_id_type id;
    };
}

#endif // __HID_PAGE_MONITOR_ENUMERATED_VALUES_H_

