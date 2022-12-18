#ifndef __HID_PAGE_BUTTON_H_
#define __HID_PAGE_BUTTON_H_

#include "hid/usage.h"

namespace hid::page
{
    class button;
    template<>
    struct info<button>
    {
        constexpr static usage_id_type base_id = 0x00090000;
        constexpr static usage_id_type max_usage = 0x00ff | base_id;
        constexpr static const char* name = "Button";
    };
    class button
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
        constexpr button(usage_index_type value)
            : id((value & USAGE_INDEX_MASK) | info<button>::base_id)
        {
        }
    private:
        usage_id_type id;
    };
}

#endif // __HID_PAGE_BUTTON_H_

