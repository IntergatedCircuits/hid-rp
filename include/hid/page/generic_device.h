#ifndef __HID_PAGE_GENERIC_DEVICE_H_
#define __HID_PAGE_GENERIC_DEVICE_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class generic_device : usage_id_type;
    template<>
    struct info<generic_device>
    {
        constexpr static usage_id_type base_id = 0x00060000;
        constexpr static usage_id_type max_usage = 0x0041 | base_id;
        constexpr static const char* name = "Generic Device Controls";
    };
    enum class generic_device : usage_id_type
    {
        BACKGROUND_CONTROLS = 0x0001 | info<generic_device>::base_id,
        BATTERY_STRENGTH = 0x0020 | info<generic_device>::base_id,
        WIRELESS_CHANNEL = 0x0021 | info<generic_device>::base_id,
        WIRELESS_ID = 0x0022 | info<generic_device>::base_id,
        DISCOVER_WIRELESS_CONTROL = 0x0023 | info<generic_device>::base_id,
        SECURITY_CODE_CHARACTER_ENTERED = 0x0024 | info<generic_device>::base_id,
        SECURITY_CODE_CHARACTER_ERASED = 0x0025 | info<generic_device>::base_id,
        SECURITY_CODE_CLEARED = 0x0026 | info<generic_device>::base_id,
        SEQUENCE_ID = 0x0027 | info<generic_device>::base_id,
        SEQUENCE_ID_RESET = 0x0028 | info<generic_device>::base_id,
        RF_SIGNAL_STRENGTH = 0x0029 | info<generic_device>::base_id,
        SOFTWARE_VERSION = 0x002a | info<generic_device>::base_id,
        PROTOCOL_VERSION = 0x002b | info<generic_device>::base_id,
        HARDWARE_VERSION = 0x002c | info<generic_device>::base_id,
        MAJOR = 0x002d | info<generic_device>::base_id,
        MINOR = 0x002e | info<generic_device>::base_id,
        REVISION = 0x002f | info<generic_device>::base_id,
        HANDEDNESS = 0x0030 | info<generic_device>::base_id,
        EITHER_HAND = 0x0031 | info<generic_device>::base_id,
        LEFT_HAND = 0x0032 | info<generic_device>::base_id,
        RIGHT_HAND = 0x0033 | info<generic_device>::base_id,
        BOTH_HANDS = 0x0034 | info<generic_device>::base_id,
        GRIP_POSE_OFFSET = 0x0040 | info<generic_device>::base_id,
        POINTER_POSE_OFFSET = 0x0041 | info<generic_device>::base_id,
    };
}

#endif // __HID_PAGE_GENERIC_DEVICE_H_

