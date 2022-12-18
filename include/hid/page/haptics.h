#ifndef __HID_PAGE_HAPTICS_H_
#define __HID_PAGE_HAPTICS_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class haptics : usage_id_type;
    template<>
    struct info<haptics>
    {
        constexpr static usage_id_type base_id = 0x000e0000;
        constexpr static usage_id_type max_usage = 0x1011 | base_id;
        constexpr static const char* name = "Haptics";
    };
    enum class haptics : usage_id_type
    {
        SIMPLE_HAPTIC_CONTROLLER = 0x0001 | info<haptics>::base_id,
        WAVEFORM_LIST = 0x0010 | info<haptics>::base_id,
        DURATION_LIST = 0x0011 | info<haptics>::base_id,
        AUTO_TRIGGER = 0x0020 | info<haptics>::base_id,
        MANUAL_TRIGGER = 0x0021 | info<haptics>::base_id,
        AUTO_TRIGGER_ASSOCIATED_CONTROL = 0x0022 | info<haptics>::base_id,
        INTENSITY = 0x0023 | info<haptics>::base_id,
        REPEAT_COUNT = 0x0024 | info<haptics>::base_id,
        RETRIGGER_PERIOD = 0x0025 | info<haptics>::base_id,
        WAVEFORM_VENDOR_PAGE = 0x0026 | info<haptics>::base_id,
        WAVEFORM_VENDOR_ID = 0x0027 | info<haptics>::base_id,
        WAVEFORM_CUTOFF_TIME = 0x0028 | info<haptics>::base_id,
        WAVEFORM_NONE = 0x1001 | info<haptics>::base_id,
        WAVEFORM_STOP = 0x1002 | info<haptics>::base_id,
        WAVEFORM_CLICK = 0x1003 | info<haptics>::base_id,
        WAVEFORM_BUZZ_CONTINUOUS = 0x1004 | info<haptics>::base_id,
        WAVEFORM_RUMBLE_CONTINUOUS = 0x1005 | info<haptics>::base_id,
        WAVEFORM_PRESS = 0x1006 | info<haptics>::base_id,
        WAVEFORM_RELEASE = 0x1007 | info<haptics>::base_id,
        WAVEFORM_HOVER = 0x1008 | info<haptics>::base_id,
        WAVEFORM_SUCCESS = 0x1009 | info<haptics>::base_id,
        WAVEFORM_ERROR = 0x100a | info<haptics>::base_id,
        WAVEFORM_INK_CONTINUOUS = 0x100b | info<haptics>::base_id,
        WAVEFORM_PENCIL_CONTINUOUS = 0x100c | info<haptics>::base_id,
        WAVEFORM_MARKER_CONTINUOUS = 0x100d | info<haptics>::base_id,
        WAVEFORM_CHISEL_MARKER_CONTINUOUS = 0x100e | info<haptics>::base_id,
        WAVEFORM_BRUSH_CONTINUOUS = 0x100f | info<haptics>::base_id,
        WAVEFORM_ERASER_CONTINUOUS = 0x1010 | info<haptics>::base_id,
        WAVEFORM_SPARKLE_CONTINUOUS = 0x1011 | info<haptics>::base_id,
    };
}

#endif // __HID_PAGE_HAPTICS_H_

