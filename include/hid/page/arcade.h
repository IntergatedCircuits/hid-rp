#ifndef __HID_PAGE_ARCADE_H_
#define __HID_PAGE_ARCADE_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class arcade : usage_id_type;
    template<>
    struct info<arcade>
    {
        constexpr static usage_id_type base_id = 0x00910000;
        constexpr static usage_id_type max_usage = 0x004d | base_id;
        constexpr static const char* name = "Arcade";
    };
    enum class arcade : usage_id_type
    {
        GENERAL_PURPOSE_IO_CARD = 0x0001 | info<arcade>::base_id,
        COIN_DOOR = 0x0002 | info<arcade>::base_id,
        WATCHDOG_TIMER = 0x0003 | info<arcade>::base_id,
        GENERAL_PURPOSE_ANALOG_INPUT_STATE = 0x0030 | info<arcade>::base_id,
        GENERAL_PURPOSE_DIGITAL_INPUT_STATE = 0x0031 | info<arcade>::base_id,
        GENERAL_PURPOSE_OPTICAL_INPUT_STATE = 0x0032 | info<arcade>::base_id,
        GENERAL_PURPOSE_DIGITAL_OUTPUT_STATE = 0x0033 | info<arcade>::base_id,
        NUMBER_OF_COIN_DOORS = 0x0034 | info<arcade>::base_id,
        COIN_DRAWER_DROP_COUNT = 0x0035 | info<arcade>::base_id,
        COIN_DRAWER_START = 0x0036 | info<arcade>::base_id,
        COIN_DRAWER_SERVICE = 0x0037 | info<arcade>::base_id,
        COIN_DRAWER_TILT = 0x0038 | info<arcade>::base_id,
        COIN_DOOR_TEST = 0x0039 | info<arcade>::base_id,
        COIN_DOOR_LOCKOUT = 0x0040 | info<arcade>::base_id,
        WATCHDOG_TIMEOUT = 0x0041 | info<arcade>::base_id,
        WATCHDOG_ACTION = 0x0042 | info<arcade>::base_id,
        WATCHDOG_REBOOT = 0x0043 | info<arcade>::base_id,
        WATCHDOG_RESTART = 0x0044 | info<arcade>::base_id,
        ALARM_INPUT = 0x0045 | info<arcade>::base_id,
        COIN_DOOR_COUNTER = 0x0046 | info<arcade>::base_id,
        I_O_DIRECTION_MAPPING = 0x0047 | info<arcade>::base_id,
        SET_I_O_DIRECTION = 0x0048 | info<arcade>::base_id,
        EXTENDED_OPTICAL_INPUT_STATE = 0x0049 | info<arcade>::base_id,
        PIN_PAD_INPUT_STATE = 0x004a | info<arcade>::base_id,
        PIN_PAD_STATUS = 0x004b | info<arcade>::base_id,
        PIN_PAD_OUTPUT = 0x004c | info<arcade>::base_id,
        PIN_PAD_COMMAND = 0x004d | info<arcade>::base_id,
    };
}

#endif // __HID_PAGE_ARCADE_H_

