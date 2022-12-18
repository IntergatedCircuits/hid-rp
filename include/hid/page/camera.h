#ifndef __HID_PAGE_CAMERA_H_
#define __HID_PAGE_CAMERA_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class camera : usage_id_type;
    template<>
    struct info<camera>
    {
        constexpr static usage_id_type base_id = 0x00900000;
        constexpr static usage_id_type max_usage = 0x0021 | base_id;
        constexpr static const char* name = "Camera Control";
    };
    enum class camera : usage_id_type
    {
        CAMERA_AUTO_FOCUS = 0x0020 | info<camera>::base_id,
        CAMERA_SHUTTER = 0x0021 | info<camera>::base_id,
    };
}

#endif // __HID_PAGE_CAMERA_H_

