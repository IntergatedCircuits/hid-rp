#ifndef __HID_PAGE_SPORT_H_
#define __HID_PAGE_SPORT_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class sport : usage_id_type;
    template<>
    struct info<sport>
    {
        constexpr static usage_id_type base_id = 0x00040000;
        constexpr static usage_id_type max_usage = 0x0063 | base_id;
        constexpr static const char* name = "Sport Controls";
    };
    enum class sport : usage_id_type
    {
        BASEBALL_BAT = 0x0001 | info<sport>::base_id,
        GOLF_CLUB = 0x0002 | info<sport>::base_id,
        ROWING_MACHINE = 0x0003 | info<sport>::base_id,
        TREADMILL = 0x0004 | info<sport>::base_id,
        OAR = 0x0030 | info<sport>::base_id,
        SLOPE = 0x0031 | info<sport>::base_id,
        RATE = 0x0032 | info<sport>::base_id,
        STICK_SPEED = 0x0033 | info<sport>::base_id,
        STICK_FACE_ANGLE = 0x0034 | info<sport>::base_id,
        STICK_HEEL_TOE = 0x0035 | info<sport>::base_id,
        STICK_FOLLOW_THROUGH = 0x0036 | info<sport>::base_id,
        STICK_TEMPO = 0x0037 | info<sport>::base_id,
        STICK_TYPE = 0x0038 | info<sport>::base_id,
        STICK_HEIGHT = 0x0039 | info<sport>::base_id,
        PUTTER = 0x0050 | info<sport>::base_id,
        _1_IRON = 0x0051 | info<sport>::base_id,
        _2_IRON = 0x0052 | info<sport>::base_id,
        _3_IRON = 0x0053 | info<sport>::base_id,
        _4_IRON = 0x0054 | info<sport>::base_id,
        _5_IRON = 0x0055 | info<sport>::base_id,
        _6_IRON = 0x0056 | info<sport>::base_id,
        _7_IRON = 0x0057 | info<sport>::base_id,
        _8_IRON = 0x0058 | info<sport>::base_id,
        _9_IRON = 0x0059 | info<sport>::base_id,
        _10_IRON = 0x005a | info<sport>::base_id,
        _11_IRON = 0x005b | info<sport>::base_id,
        SAND_WEDGE = 0x005c | info<sport>::base_id,
        LOFT_WEDGE = 0x005d | info<sport>::base_id,
        POWER_WEDGE = 0x005e | info<sport>::base_id,
        _1_WOOD = 0x005f | info<sport>::base_id,
        _3_WOOD = 0x0060 | info<sport>::base_id,
        _5_WOOD = 0x0061 | info<sport>::base_id,
        _7_WOOD = 0x0062 | info<sport>::base_id,
        _9_WOOD = 0x0063 | info<sport>::base_id,
    };
}

#endif // __HID_PAGE_SPORT_H_

