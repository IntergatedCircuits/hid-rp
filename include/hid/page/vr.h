#ifndef __HID_PAGE_VR_H_
#define __HID_PAGE_VR_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class vr : usage_id_type;
    template<>
    struct info<vr>
    {
        constexpr static usage_id_type base_id = 0x00030000;
        constexpr static usage_id_type max_usage = 0x0021 | base_id;
        constexpr static const char* name = "VR Controls";
    };
    enum class vr : usage_id_type
    {
        BELT = 0x0001 | info<vr>::base_id,
        BODY_SUIT = 0x0002 | info<vr>::base_id,
        FLEXOR = 0x0003 | info<vr>::base_id,
        GLOVE = 0x0004 | info<vr>::base_id,
        HEAD_TRACKER = 0x0005 | info<vr>::base_id,
        HEAD_MOUNTED_DISPLAY = 0x0006 | info<vr>::base_id,
        HAND_TRACKER = 0x0007 | info<vr>::base_id,
        OCULOMETER = 0x0008 | info<vr>::base_id,
        VEST = 0x0009 | info<vr>::base_id,
        ANIMATRONIC_DEVICE = 0x000a | info<vr>::base_id,
        STEREO_ENABLE = 0x0020 | info<vr>::base_id,
        DISPLAY_ENABLE = 0x0021 | info<vr>::base_id,
    };
}

#endif // __HID_PAGE_VR_H_

