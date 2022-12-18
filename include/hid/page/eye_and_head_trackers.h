#ifndef __HID_PAGE_EYE_AND_HEAD_TRACKERS_H_
#define __HID_PAGE_EYE_AND_HEAD_TRACKERS_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class eye_and_head_trackers : usage_id_type;
    template<>
    struct info<eye_and_head_trackers>
    {
        constexpr static usage_id_type base_id = 0x00120000;
        constexpr static usage_id_type max_usage = 0x0400 | base_id;
        constexpr static const char* name = "Eye and Head Trackers";
    };
    enum class eye_and_head_trackers : usage_id_type
    {
        EYE_TRACKER = 0x0001 | info<eye_and_head_trackers>::base_id,
        HEAD_TRACKER = 0x0002 | info<eye_and_head_trackers>::base_id,
        TRACKING_DATA = 0x0010 | info<eye_and_head_trackers>::base_id,
        CAPABILITIES = 0x0011 | info<eye_and_head_trackers>::base_id,
        CONFIGURATION = 0x0012 | info<eye_and_head_trackers>::base_id,
        STATUS = 0x0013 | info<eye_and_head_trackers>::base_id,
        CONTROL = 0x0014 | info<eye_and_head_trackers>::base_id,
        SENSOR_TIMESTAMP = 0x0020 | info<eye_and_head_trackers>::base_id,
        POSITION_X = 0x0021 | info<eye_and_head_trackers>::base_id,
        POSITION_Y = 0x0022 | info<eye_and_head_trackers>::base_id,
        POSITION_Z = 0x0023 | info<eye_and_head_trackers>::base_id,
        GAZE_POINT = 0x0024 | info<eye_and_head_trackers>::base_id,
        LEFT_EYE_POSITION = 0x0025 | info<eye_and_head_trackers>::base_id,
        RIGHT_EYE_POSITION = 0x0026 | info<eye_and_head_trackers>::base_id,
        HEAD_POSITION = 0x0027 | info<eye_and_head_trackers>::base_id,
        HEAD_DIRECTION_POINT = 0x0028 | info<eye_and_head_trackers>::base_id,
        ROTATION_ABOUT_X_AXIS = 0x0029 | info<eye_and_head_trackers>::base_id,
        ROTATION_ABOUT_Y_AXIS = 0x002a | info<eye_and_head_trackers>::base_id,
        ROTATION_ABOUT_Z_AXIS = 0x002b | info<eye_and_head_trackers>::base_id,
        TRACKER_QUALITY = 0x0100 | info<eye_and_head_trackers>::base_id,
        MINIMUM_TRACKING_DISTANCE = 0x0101 | info<eye_and_head_trackers>::base_id,
        OPTIMUM_TRACKING_DISTANCE = 0x0102 | info<eye_and_head_trackers>::base_id,
        MAXIMUM_TRACKING_DISTANCE = 0x0103 | info<eye_and_head_trackers>::base_id,
        MAXIMUM_SCREEN_PLANE_WIDTH = 0x0104 | info<eye_and_head_trackers>::base_id,
        MAXIMUM_SCREEN_PLANE_HEIGHT = 0x0105 | info<eye_and_head_trackers>::base_id,
        DISPLAY_MANUFACTURER_ID = 0x0200 | info<eye_and_head_trackers>::base_id,
        DISPLAY_PRODUCT_ID = 0x0201 | info<eye_and_head_trackers>::base_id,
        DISPLAY_SERIAL_NUMBER = 0x0202 | info<eye_and_head_trackers>::base_id,
        DISPLAY_MANUFACTURER_DATE = 0x0203 | info<eye_and_head_trackers>::base_id,
        CALIBRATED_SCREEN_WIDTH = 0x0204 | info<eye_and_head_trackers>::base_id,
        CALIBRATED_SCREEN_HEIGHT = 0x0205 | info<eye_and_head_trackers>::base_id,
        SAMPLING_FREQUENCY = 0x0300 | info<eye_and_head_trackers>::base_id,
        CONFIGURATION_STATUS = 0x0301 | info<eye_and_head_trackers>::base_id,
        DEVICE_MODE_REQUEST = 0x0400 | info<eye_and_head_trackers>::base_id,
    };
}

#endif // __HID_PAGE_EYE_AND_HEAD_TRACKERS_H_

