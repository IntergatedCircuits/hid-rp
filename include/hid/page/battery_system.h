#ifndef __HID_PAGE_BATTERY_SYSTEM_H_
#define __HID_PAGE_BATTERY_SYSTEM_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class battery_system : usage_id_type;
    template<>
    struct info<battery_system>
    {
        constexpr static usage_id_type base_id = 0x00850000;
        constexpr static usage_id_type max_usage = 0x00f3 | base_id;
        constexpr static const char* name = "Battery System";
    };
    enum class battery_system : usage_id_type
    {
        SMB_BATTERY_MODE = 0x0001 | info<battery_system>::base_id,
        SMB_BATTERY_STATUS = 0x0002 | info<battery_system>::base_id,
        SMB_ALARM_WARNING = 0x0003 | info<battery_system>::base_id,
        SMB_CHARGER_MODE = 0x0004 | info<battery_system>::base_id,
        SMB_CHARGER_STATUS = 0x0005 | info<battery_system>::base_id,
        SMB_CHARGER_SPEC_INFO = 0x0006 | info<battery_system>::base_id,
        SMB_SELECTOR_STATE = 0x0007 | info<battery_system>::base_id,
        SMB_SELECTOR_PRESETS = 0x0008 | info<battery_system>::base_id,
        SMB_SELECTOR_INFO = 0x0009 | info<battery_system>::base_id,
        OPTIONAL_MFG_FUNCTION_1 = 0x0010 | info<battery_system>::base_id,
        OPTIONAL_MFG_FUNCTION_2 = 0x0011 | info<battery_system>::base_id,
        OPTIONAL_MFG_FUNCTION_3 = 0x0012 | info<battery_system>::base_id,
        OPTIONAL_MFG_FUNCTION_4 = 0x0013 | info<battery_system>::base_id,
        OPTIONAL_MFG_FUNCTION_5 = 0x0014 | info<battery_system>::base_id,
        CONNECTION_TO_SMBUS = 0x0015 | info<battery_system>::base_id,
        OUTPUT_CONNECTION = 0x0016 | info<battery_system>::base_id,
        CHARGER_CONNECTION = 0x0017 | info<battery_system>::base_id,
        BATTERY_INSERTION = 0x0018 | info<battery_system>::base_id,
        USE_NEXT = 0x0019 | info<battery_system>::base_id,
        OK_TO_USE = 0x001a | info<battery_system>::base_id,
        BATTERY_SUPPORTED = 0x001b | info<battery_system>::base_id,
        SELECTOR_REVISION = 0x001c | info<battery_system>::base_id,
        CHARGING_INDICATOR = 0x001d | info<battery_system>::base_id,
        MANUFACTURER_ACCESS = 0x0028 | info<battery_system>::base_id,
        REMAINING_CAPACITY_LIMIT = 0x0029 | info<battery_system>::base_id,
        REMAINING_TIME_LIMIT = 0x002a | info<battery_system>::base_id,
        AT_RATE = 0x002b | info<battery_system>::base_id,
        CAPACITY_MODE = 0x002c | info<battery_system>::base_id,
        BROADCAST_TO_CHARGER = 0x002d | info<battery_system>::base_id,
        PRIMARY_BATTERY = 0x002e | info<battery_system>::base_id,
        CHARGE_CONTROLLER = 0x002f | info<battery_system>::base_id,
        TERMINATE_CHARGE = 0x0040 | info<battery_system>::base_id,
        TERMINATE_DISCHARGE = 0x0041 | info<battery_system>::base_id,
        BELOW_REMAINING_CAPACITY_LIMIT = 0x0042 | info<battery_system>::base_id,
        REMAINING_TIME_LIMIT_EXPIRED = 0x0043 | info<battery_system>::base_id,
        CHARGING = 0x0044 | info<battery_system>::base_id,
        DISCHARGING = 0x0045 | info<battery_system>::base_id,
        FULLY_CHARGED = 0x0046 | info<battery_system>::base_id,
        FULLY_DISCHARGED = 0x0047 | info<battery_system>::base_id,
        CONDITIONING_FLAG = 0x0048 | info<battery_system>::base_id,
        AT_RATE_OK = 0x0049 | info<battery_system>::base_id,
        SMB_ERROR_CODE = 0x004a | info<battery_system>::base_id,
        NEED_REPLACEMENT = 0x004b | info<battery_system>::base_id,
        AT_RATE_TIME_TO_FULL = 0x0060 | info<battery_system>::base_id,
        AT_RATE_TIME_TO_EMPTY = 0x0061 | info<battery_system>::base_id,
        AVERAGE_CURRENT = 0x0062 | info<battery_system>::base_id,
        MAX_ERROR = 0x0063 | info<battery_system>::base_id,
        RELATIVE_STATE_OF_CHARGE = 0x0064 | info<battery_system>::base_id,
        ABSOLUTE_STATE_OF_CHARGE = 0x0065 | info<battery_system>::base_id,
        REMAINING_CAPACITY = 0x0066 | info<battery_system>::base_id,
        FULL_CHARGE_CAPACITY = 0x0067 | info<battery_system>::base_id,
        RUN_TIME_TO_EMPTY = 0x0068 | info<battery_system>::base_id,
        AVERAGE_TIME_TO_EMPTY = 0x0069 | info<battery_system>::base_id,
        AVERAGE_TIME_TO_FULL = 0x006a | info<battery_system>::base_id,
        CYCLE_COUNT = 0x006b | info<battery_system>::base_id,
        BATTERY_PACK_MODEL_LEVEL = 0x0080 | info<battery_system>::base_id,
        INTERNAL_CHARGE_CONTROLLER = 0x0081 | info<battery_system>::base_id,
        PRIMARY_BATTERY_SUPPORT = 0x0082 | info<battery_system>::base_id,
        DESIGN_CAPACITY = 0x0083 | info<battery_system>::base_id,
        SPECIFICATION_INFO = 0x0084 | info<battery_system>::base_id,
        MANUFACTURER_DATE = 0x0085 | info<battery_system>::base_id,
        SERIAL_NUMBER = 0x0086 | info<battery_system>::base_id,
        IMANUFACTURER = 0x0087 | info<battery_system>::base_id,
        IDEVICENAME = 0x0088 | info<battery_system>::base_id,
        IDEVICECHEMISTRY = 0x0089 | info<battery_system>::base_id,
        MANUFACTURER_DATA = 0x008a | info<battery_system>::base_id,
        RECHARGEABLE = 0x008b | info<battery_system>::base_id,
        WARNING_CAPACITY_LIMIT = 0x008c | info<battery_system>::base_id,
        CAPACITY_GRANULARITY_1 = 0x008d | info<battery_system>::base_id,
        CAPACITY_GRANULARITY_2 = 0x008e | info<battery_system>::base_id,
        IOEMINFORMATION = 0x008f | info<battery_system>::base_id,
        INHIBIT_CHARGE = 0x00c0 | info<battery_system>::base_id,
        ENABLE_POLLING = 0x00c1 | info<battery_system>::base_id,
        RESET_TO_ZERO = 0x00c2 | info<battery_system>::base_id,
        AC_PRESENT = 0x00d0 | info<battery_system>::base_id,
        BATTERY_PRESENT = 0x00d1 | info<battery_system>::base_id,
        POWER_FAIL = 0x00d2 | info<battery_system>::base_id,
        ALARM_INHIBITED = 0x00d3 | info<battery_system>::base_id,
        THERMISTOR_UNDER_RANGE = 0x00d4 | info<battery_system>::base_id,
        THERMISTOR_HOT = 0x00d5 | info<battery_system>::base_id,
        THERMISTOR_COLD = 0x00d6 | info<battery_system>::base_id,
        THERMISTOR_OVER_RANGE = 0x00d7 | info<battery_system>::base_id,
        VOLTAGE_OUT_OF_RANGE = 0x00d8 | info<battery_system>::base_id,
        CURRENT_OUT_OF_RANGE = 0x00d9 | info<battery_system>::base_id,
        CURRENT_NOT_REGULATED = 0x00da | info<battery_system>::base_id,
        VOLTAGE_NOT_REGULATED = 0x00db | info<battery_system>::base_id,
        MASTER_MODE = 0x00dc | info<battery_system>::base_id,
        CHARGER_SELECTOR_SUPPORT = 0x00f0 | info<battery_system>::base_id,
        CHARGER_SPEC = 0x00f1 | info<battery_system>::base_id,
        LEVEL_2 = 0x00f2 | info<battery_system>::base_id,
        LEVEL_3 = 0x00f3 | info<battery_system>::base_id,
    };
}

#endif // __HID_PAGE_BATTERY_SYSTEM_H_

