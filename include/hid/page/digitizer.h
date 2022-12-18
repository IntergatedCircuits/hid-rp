#ifndef __HID_PAGE_DIGITIZER_H_
#define __HID_PAGE_DIGITIZER_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class digitizer : usage_id_type;
    template<>
    struct info<digitizer>
    {
        constexpr static usage_id_type base_id = 0x000d0000;
        constexpr static usage_id_type max_usage = 0x00a5 | base_id;
        constexpr static const char* name = "Digitizer";
    };
    enum class digitizer : usage_id_type
    {
        DIGITIZER = 0x0001 | info<digitizer>::base_id,
        PEN = 0x0002 | info<digitizer>::base_id,
        LIGHT_PEN = 0x0003 | info<digitizer>::base_id,
        TOUCH_SCREEN = 0x0004 | info<digitizer>::base_id,
        TOUCH_PAD = 0x0005 | info<digitizer>::base_id,
        WHITE_BOARD = 0x0006 | info<digitizer>::base_id,
        COORDINATE_MEASURING_MACHINE = 0x0007 | info<digitizer>::base_id,
        _3D_DIGITIZER = 0x0008 | info<digitizer>::base_id,
        STEREO_PLOTTER = 0x0009 | info<digitizer>::base_id,
        ARTICULATED_ARM = 0x000a | info<digitizer>::base_id,
        ARMATURE = 0x000b | info<digitizer>::base_id,
        MULTIPLE_POINT_DIGITIZER = 0x000c | info<digitizer>::base_id,
        FREE_SPACE_WAND = 0x000d | info<digitizer>::base_id,
        DEVICE_CONFIGURATION = 0x000e | info<digitizer>::base_id,
        CAPACITIVE_HEAT_MAP_DIGITIZER = 0x000f | info<digitizer>::base_id,
        STYLUS = 0x0020 | info<digitizer>::base_id,
        PUCK = 0x0021 | info<digitizer>::base_id,
        FINGER = 0x0022 | info<digitizer>::base_id,
        DEVICE_SETTINGS = 0x0023 | info<digitizer>::base_id,
        CHARACTER_GESTURE = 0x0024 | info<digitizer>::base_id,
        TIP_PRESSURE = 0x0030 | info<digitizer>::base_id,
        BARREL_PRESSURE = 0x0031 | info<digitizer>::base_id,
        IN_RANGE = 0x0032 | info<digitizer>::base_id,
        TOUCH = 0x0033 | info<digitizer>::base_id,
        UNTOUCH = 0x0034 | info<digitizer>::base_id,
        TAP = 0x0035 | info<digitizer>::base_id,
        QUALITY = 0x0036 | info<digitizer>::base_id,
        DATA_VALID = 0x0037 | info<digitizer>::base_id,
        TRANSDUCER_INDEX = 0x0038 | info<digitizer>::base_id,
        TABLET_FUNCTION_KEYS = 0x0039 | info<digitizer>::base_id,
        PROGRAM_CHANGE_KEYS = 0x003a | info<digitizer>::base_id,
        BATTERY_STRENGTH = 0x003b | info<digitizer>::base_id,
        INVERT = 0x003c | info<digitizer>::base_id,
        X_TILT = 0x003d | info<digitizer>::base_id,
        Y_TILT = 0x003e | info<digitizer>::base_id,
        AZIMUTH = 0x003f | info<digitizer>::base_id,
        ALTITUDE = 0x0040 | info<digitizer>::base_id,
        TWIST = 0x0041 | info<digitizer>::base_id,
        TIP_SWITCH = 0x0042 | info<digitizer>::base_id,
        SECONDARY_TIP_SWITCH = 0x0043 | info<digitizer>::base_id,
        BARREL_SWITCH = 0x0044 | info<digitizer>::base_id,
        ERASER = 0x0045 | info<digitizer>::base_id,
        TABLET_PICK = 0x0046 | info<digitizer>::base_id,
        TOUCH_VALID = 0x0047 | info<digitizer>::base_id,
        WIDTH = 0x0048 | info<digitizer>::base_id,
        HEIGHT = 0x0049 | info<digitizer>::base_id,
        CONTACT_IDENTIFIER = 0x0051 | info<digitizer>::base_id,
        DEVICE_MODE = 0x0052 | info<digitizer>::base_id,
        DEVICE_IDENTIFIER = 0x0053 | info<digitizer>::base_id,
        CONTACT_COUNT = 0x0054 | info<digitizer>::base_id,
        CONTACT_COUNT_MAXIMUM = 0x0055 | info<digitizer>::base_id,
        SCAN_TIME = 0x0056 | info<digitizer>::base_id,
        SURFACE_WIDTH = 0x0057 | info<digitizer>::base_id,
        BUTTON_SWITCH = 0x0058 | info<digitizer>::base_id,
        PAD_TYPE = 0x0059 | info<digitizer>::base_id,
        SECONDARY_BARREL_SWITCH = 0x005a | info<digitizer>::base_id,
        TRANSDUCER_SERIAL_NUMBER = 0x005b | info<digitizer>::base_id,
        PREFERRED_COLOR = 0x005c | info<digitizer>::base_id,
        LATENCY_MODE = 0x0060 | info<digitizer>::base_id,
        GESTURE_CHARACTER_QUALITY = 0x0061 | info<digitizer>::base_id,
        CHARACTER_GESTURE_DATA_LENGTH = 0x0062 | info<digitizer>::base_id,
        CHARACTER_GESTURE_DATA = 0x0063 | info<digitizer>::base_id,
        GESTURE_CHARACTER_ENCODING = 0x0064 | info<digitizer>::base_id,
        UTF8_CHARACTER_GESTURE_ENCODING = 0x0065 | info<digitizer>::base_id,
        UTF16_LITTLE_ENDIAN_CHARACTER_GESTURE_ENCODING = 0x0066 | info<digitizer>::base_id,
        UTF16_BIG_ENDIAN_CHARACTER_GESTURE_ENCODING = 0x0067 | info<digitizer>::base_id,
        UTF32_LITTLE_ENDIAN_CHARACTER_GESTURE_ENCODING = 0x0068 | info<digitizer>::base_id,
        UTF32_BIG_ENDIAN_CHARACTER_GESTURE_ENCODING = 0x0069 | info<digitizer>::base_id,
        CAPACITIVE_HEAT_MAP_PROTOCOL_VENDOR_ID = 0x006a | info<digitizer>::base_id,
        CAPACITIVE_HEAT_MAP_PROTOCOL_VERSION = 0x006b | info<digitizer>::base_id,
        CAPACITIVE_HEAT_MAP_FRAME_DATA = 0x006c | info<digitizer>::base_id,
        GESTURE_CHARACTER_ENABLE = 0x006d | info<digitizer>::base_id,
        TRANSDUCER_SERIAL_NUMBER_PART_2 = 0x006e | info<digitizer>::base_id,
        NO_PREFERRED_COLOR = 0x006f | info<digitizer>::base_id,
        TRANSDUCER_SOFTWARE_INFO = 0x0090 | info<digitizer>::base_id,
        TRANSDUCER_VENDOR_ID = 0x0091 | info<digitizer>::base_id,
        TRANSDUCER_PRODUCT_ID = 0x0092 | info<digitizer>::base_id,
        DEVICE_SUPPORTED_PROTOCOLS = 0x0093 | info<digitizer>::base_id,
        TRANSDUCER_SUPPORTED_PROTOCOLS = 0x0094 | info<digitizer>::base_id,
        NO_PROTOCOL = 0x0095 | info<digitizer>::base_id,
        WACOM_AES_PROTOCOL = 0x0096 | info<digitizer>::base_id,
        USI_PROTOCOL = 0x0097 | info<digitizer>::base_id,
        MICROSOFT_PEN_PROTOCOL = 0x0098 | info<digitizer>::base_id,
        SUPPORTED_REPORT_RATES = 0x00a0 | info<digitizer>::base_id,
        REPORT_RATE = 0x00a1 | info<digitizer>::base_id,
        TRANSDUCER_CONNECTED = 0x00a2 | info<digitizer>::base_id,
        SWITCH_DISABLED = 0x00a3 | info<digitizer>::base_id,
        SWITCH_UNIMPLEMENTED = 0x00a4 | info<digitizer>::base_id,
        TRANSDUCER_SWITCHES = 0x00a5 | info<digitizer>::base_id,
    };
}

#endif // __HID_PAGE_DIGITIZER_H_

