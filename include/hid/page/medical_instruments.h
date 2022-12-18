#ifndef __HID_PAGE_MEDICAL_INSTRUMENTS_H_
#define __HID_PAGE_MEDICAL_INSTRUMENTS_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class medical_instruments : usage_id_type;
    template<>
    struct info<medical_instruments>
    {
        constexpr static usage_id_type base_id = 0x00400000;
        constexpr static usage_id_type max_usage = 0x00a1 | base_id;
        constexpr static const char* name = "Medical Instruments";
    };
    enum class medical_instruments : usage_id_type
    {
        MEDICAL_ULTRASOUND = 0x0001 | info<medical_instruments>::base_id,
        VCR_ACQUISITION = 0x0020 | info<medical_instruments>::base_id,
        FREEZE_THAW = 0x0021 | info<medical_instruments>::base_id,
        CLIP_STORE = 0x0022 | info<medical_instruments>::base_id,
        UPDATE = 0x0023 | info<medical_instruments>::base_id,
        NEXT = 0x0024 | info<medical_instruments>::base_id,
        SAVE = 0x0025 | info<medical_instruments>::base_id,
        PRINT = 0x0026 | info<medical_instruments>::base_id,
        MICROPHONE_ENABLE = 0x0027 | info<medical_instruments>::base_id,
        CINE = 0x0040 | info<medical_instruments>::base_id,
        TRANSMIT_POWER = 0x0041 | info<medical_instruments>::base_id,
        VOLUME = 0x0042 | info<medical_instruments>::base_id,
        FOCUS = 0x0043 | info<medical_instruments>::base_id,
        DEPTH = 0x0044 | info<medical_instruments>::base_id,
        SOFT_STEP_PRIMARY = 0x0060 | info<medical_instruments>::base_id,
        SOFT_STEP_SECONDARY = 0x0061 | info<medical_instruments>::base_id,
        DEPTH_GAIN_COMPENSATION = 0x0070 | info<medical_instruments>::base_id,
        ZOOM_SELECT = 0x0080 | info<medical_instruments>::base_id,
        ZOOM_ADJUST = 0x0081 | info<medical_instruments>::base_id,
        SPECTRAL_DOPPLER_MODE_SELECT = 0x0082 | info<medical_instruments>::base_id,
        SPECTRAL_DOPPLER_ADJUST = 0x0083 | info<medical_instruments>::base_id,
        COLOR_DOPPLER_MODE_SELECT = 0x0084 | info<medical_instruments>::base_id,
        COLOR_DOPPLER_ADJUST = 0x0085 | info<medical_instruments>::base_id,
        MOTION_MODE_SELECT = 0x0086 | info<medical_instruments>::base_id,
        MOTION_MODE_ADJUST = 0x0087 | info<medical_instruments>::base_id,
        _2D_MODE_SELECT = 0x0088 | info<medical_instruments>::base_id,
        _2D_MODE_ADJUST = 0x0089 | info<medical_instruments>::base_id,
        SOFT_CONTROL_SELECT = 0x00a0 | info<medical_instruments>::base_id,
        SOFT_CONTROL_ADJUST = 0x00a1 | info<medical_instruments>::base_id,
    };
}

#endif // __HID_PAGE_MEDICAL_INSTRUMENTS_H_

