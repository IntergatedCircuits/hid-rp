#ifndef __HID_PAGE_LIGHTING_AND_ILLUMINATION_H_
#define __HID_PAGE_LIGHTING_AND_ILLUMINATION_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class lighting_and_illumination : usage_id_type;
    template<>
    struct info<lighting_and_illumination>
    {
        constexpr static usage_id_type base_id = 0x00590000;
        constexpr static usage_id_type max_usage = 0x0071 | base_id;
        constexpr static const char* name = "Lighting and Illumination";
    };
    enum class lighting_and_illumination : usage_id_type
    {
        LAMP_ARRAY = 0x0001 | info<lighting_and_illumination>::base_id,
        LAMP_ARRAY_ATTRIBUTES_REPORT = 0x0002 | info<lighting_and_illumination>::base_id,
        LAMP_COUNT = 0x0003 | info<lighting_and_illumination>::base_id,
        BOUNDING_BOX_WIDTH_UM = 0x0004 | info<lighting_and_illumination>::base_id,
        BOUNDING_BOX_HEIGHT_UM = 0x0005 | info<lighting_and_illumination>::base_id,
        BOUNDING_BOX_DEPTH_UM = 0x0006 | info<lighting_and_illumination>::base_id,
        LAMP_ARRAY_KIND = 0x0007 | info<lighting_and_illumination>::base_id,
        MINIMAL_UPDATE_INTERVAL_US = 0x0008 | info<lighting_and_illumination>::base_id,
        LAMP_ATTRIBUTES_REQUEST_REPORT = 0x0020 | info<lighting_and_illumination>::base_id,
        LAMP_ID = 0x0021 | info<lighting_and_illumination>::base_id,
        LAMP_ATTRIBUTES_RESPONSE_REPORT = 0x0022 | info<lighting_and_illumination>::base_id,
        POSITION_X_UM = 0x0023 | info<lighting_and_illumination>::base_id,
        POSITION_Y_UM = 0x0024 | info<lighting_and_illumination>::base_id,
        POSITION_Z_UM = 0x0025 | info<lighting_and_illumination>::base_id,
        LAMP_PURPOSES = 0x0026 | info<lighting_and_illumination>::base_id,
        UPDATE_LATENCY_US = 0x0027 | info<lighting_and_illumination>::base_id,
        RED_LEVEL_COUNT = 0x0028 | info<lighting_and_illumination>::base_id,
        GREEN_LEVEL_COUNT = 0x0029 | info<lighting_and_illumination>::base_id,
        BLUE_LEVEL_COUNT = 0x002a | info<lighting_and_illumination>::base_id,
        INTENSITY_LEVEL_COUNT = 0x002b | info<lighting_and_illumination>::base_id,
        PROGRAMMABLE = 0x002c | info<lighting_and_illumination>::base_id,
        INPUT_BINDING = 0x002d | info<lighting_and_illumination>::base_id,
        LAMP_MULTI_UPDATE_REPORT = 0x0050 | info<lighting_and_illumination>::base_id,
        RED_UPDATE_CHANNEL = 0x0051 | info<lighting_and_illumination>::base_id,
        GREEN_UPDATE_CHANNEL = 0x0052 | info<lighting_and_illumination>::base_id,
        BLUE_UPDATE_CHANNEL = 0x0053 | info<lighting_and_illumination>::base_id,
        INTENSITY_UPDATE_CHANNEL = 0x0054 | info<lighting_and_illumination>::base_id,
        LAMP_UPDATE_FLAGS = 0x0055 | info<lighting_and_illumination>::base_id,
        LAMP_RANGE_UPDATE_REPORT = 0x0060 | info<lighting_and_illumination>::base_id,
        LAMP_ID_START = 0x0061 | info<lighting_and_illumination>::base_id,
        LAMP_ID_END = 0x0062 | info<lighting_and_illumination>::base_id,
        LAMP_ARRAY_CONTROL_REPORT = 0x0070 | info<lighting_and_illumination>::base_id,
        AUTONOMOUS_MODE = 0x0071 | info<lighting_and_illumination>::base_id,
    };
}

#endif // __HID_PAGE_LIGHTING_AND_ILLUMINATION_H_

