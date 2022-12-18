#ifndef __HID_PAGE_POWER_DEVICE_H_
#define __HID_PAGE_POWER_DEVICE_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class power_device : usage_id_type;
    template<>
    struct info<power_device>
    {
        constexpr static usage_id_type base_id = 0x00840000;
        constexpr static usage_id_type max_usage = 0x00ff | base_id;
        constexpr static const char* name = "Power Device";
    };
    enum class power_device : usage_id_type
    {
        INAME = 0x0001 | info<power_device>::base_id,
        PRESENT_STATUS = 0x0002 | info<power_device>::base_id,
        CHANGED_STATUS = 0x0003 | info<power_device>::base_id,
        UPS = 0x0004 | info<power_device>::base_id,
        POWER_SUPPLY = 0x0005 | info<power_device>::base_id,
        PERIPHERAL_DEVICE = 0x0006 | info<power_device>::base_id,
        BATTERY_SYSTEM = 0x0010 | info<power_device>::base_id,
        BATTERY_SYSTEM_ID = 0x0011 | info<power_device>::base_id,
        BATTERY = 0x0012 | info<power_device>::base_id,
        BATTERY_ID = 0x0013 | info<power_device>::base_id,
        CHARGER = 0x0014 | info<power_device>::base_id,
        CHARGER_ID = 0x0015 | info<power_device>::base_id,
        POWER_CONVERTER = 0x0016 | info<power_device>::base_id,
        POWER_CONVERTER_ID = 0x0017 | info<power_device>::base_id,
        OUTLET_SYSTEM = 0x0018 | info<power_device>::base_id,
        OUTLET_SYSTEM_ID = 0x0019 | info<power_device>::base_id,
        INPUT = 0x001a | info<power_device>::base_id,
        INPUT_ID = 0x001b | info<power_device>::base_id,
        OUTPUT = 0x001c | info<power_device>::base_id,
        OUTPUT_ID = 0x001d | info<power_device>::base_id,
        FLOW = 0x001e | info<power_device>::base_id,
        FLOW_ID = 0x001f | info<power_device>::base_id,
        OUTLET = 0x0020 | info<power_device>::base_id,
        OUTLET_ID = 0x0021 | info<power_device>::base_id,
        POWER_SUMMARY = 0x0022 | info<power_device>::base_id,
        POWER_SUMMARY_ID = 0x0023 | info<power_device>::base_id,
        VOLTAGE = 0x0030 | info<power_device>::base_id,
        CURRENT = 0x0031 | info<power_device>::base_id,
        FREQUENCY = 0x0032 | info<power_device>::base_id,
        APPARENT_POWER = 0x0033 | info<power_device>::base_id,
        ACTIVE_POWER = 0x0034 | info<power_device>::base_id,
        LOAD_PERCENT = 0x0035 | info<power_device>::base_id,
        TEMPERATURE = 0x0036 | info<power_device>::base_id,
        HUMIDITY = 0x0037 | info<power_device>::base_id,
        BAD_COUNT = 0x0038 | info<power_device>::base_id,
        NOMINAL_VOLTAGE = 0x0040 | info<power_device>::base_id,
        NOMINAL_CURRENT = 0x0041 | info<power_device>::base_id,
        NOMINAL_FREQUENCY = 0x0042 | info<power_device>::base_id,
        NOMINAL_APPARENT_POWER = 0x0043 | info<power_device>::base_id,
        NOMINAL_ACTIVE_POWER = 0x0044 | info<power_device>::base_id,
        NOMINAL_LOAD_PERCENT = 0x0045 | info<power_device>::base_id,
        NOMINAL_TEMPERATURE = 0x0046 | info<power_device>::base_id,
        NOMINAL_HUMIDITY = 0x0047 | info<power_device>::base_id,
        SWITCH_ON_CONTROL = 0x0050 | info<power_device>::base_id,
        SWITCH_OFF_CONTROL = 0x0051 | info<power_device>::base_id,
        TOGGLE_CONTROL = 0x0052 | info<power_device>::base_id,
        LOW_VOLTAGE_TRANSFER = 0x0053 | info<power_device>::base_id,
        HIGH_VOLTAGE_TRANSFER = 0x0054 | info<power_device>::base_id,
        DELAY_BEFORE_REBOOT = 0x0055 | info<power_device>::base_id,
        DELAY_BEFORE_STARTUP = 0x0056 | info<power_device>::base_id,
        DELAY_BEFORE_SHUTDOWN = 0x0057 | info<power_device>::base_id,
        TEST = 0x0058 | info<power_device>::base_id,
        MODULE_RESET = 0x0059 | info<power_device>::base_id,
        AUDIBLE_ALARM_CONTROL = 0x005a | info<power_device>::base_id,
        PRESENT = 0x0060 | info<power_device>::base_id,
        GOOD = 0x0061 | info<power_device>::base_id,
        INTERNAL_FAILURE = 0x0062 | info<power_device>::base_id,
        VOLTAGE_OUT_OF_RANGE = 0x0063 | info<power_device>::base_id,
        FREQUENCY_OUT_OF_RANGE = 0x0064 | info<power_device>::base_id,
        OVERLOAD = 0x0065 | info<power_device>::base_id,
        OVERCHARGED = 0x0066 | info<power_device>::base_id,
        OVER_TEMPERATURE = 0x0067 | info<power_device>::base_id,
        SHUTDOWN_REQUESTED = 0x0068 | info<power_device>::base_id,
        SHUTDOWN_IMMINENT = 0x0069 | info<power_device>::base_id,
        SWITCH_ON_OFF = 0x006b | info<power_device>::base_id,
        SWITCHABLE = 0x006c | info<power_device>::base_id,
        USED = 0x006d | info<power_device>::base_id,
        BOOST = 0x006e | info<power_device>::base_id,
        BUCK = 0x006f | info<power_device>::base_id,
        INITIALIZED = 0x0070 | info<power_device>::base_id,
        TESTED = 0x0071 | info<power_device>::base_id,
        AWAITING_POWER = 0x0072 | info<power_device>::base_id,
        COMMUNICATION_LOST = 0x0073 | info<power_device>::base_id,
        IMANUFACTURER = 0x00fd | info<power_device>::base_id,
        IPRODUCT = 0x00fe | info<power_device>::base_id,
        ISERIALNUMBER = 0x00ff | info<power_device>::base_id,
    };
}

#endif // __HID_PAGE_POWER_DEVICE_H_

