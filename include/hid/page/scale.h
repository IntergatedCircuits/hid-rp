#ifndef __HID_PAGE_SCALE_H_
#define __HID_PAGE_SCALE_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class scale : usage_id_type;
    template<>
    struct info<scale>
    {
        constexpr static usage_id_type base_id = 0x008d0000;
        constexpr static usage_id_type max_usage = 0x0081 | base_id;
        constexpr static const char* name = "Weighing Devices";
    };
    enum class scale : usage_id_type
    {
        WEIGHING_DEVICE = 0x0001 | info<scale>::base_id,
        SCALE_DEVICE = 0x0020 | info<scale>::base_id,
        // "SCALE CLASS I METRIC" = 0x0021 | info<scale>::base_id,
        // "SCALE CLASS I METRIC" = 0x0022 | info<scale>::base_id,
        SCALE_CLASS_II_METRIC = 0x0023 | info<scale>::base_id,
        SCALE_CLASS_III_METRIC = 0x0024 | info<scale>::base_id,
        SCALE_CLASS_IIIL_METRIC = 0x0025 | info<scale>::base_id,
        SCALE_CLASS_IV_METRIC = 0x0026 | info<scale>::base_id,
        SCALE_CLASS_III_ENGLISH = 0x0027 | info<scale>::base_id,
        SCALE_CLASS_IIIL_ENGLISH = 0x0028 | info<scale>::base_id,
        SCALE_CLASS_IV_ENGLISH = 0x0029 | info<scale>::base_id,
        SCALE_CLASS_GENERIC = 0x002a | info<scale>::base_id,
        SCALE_ATTRIBUTE_REPORT = 0x0030 | info<scale>::base_id,
        SCALE_CONTROL_REPORT = 0x0031 | info<scale>::base_id,
        SCALE_DATA_REPORT = 0x0032 | info<scale>::base_id,
        SCALE_STATUS_REPORT = 0x0033 | info<scale>::base_id,
        SCALE_WEIGHT_LIMIT_REPORT = 0x0034 | info<scale>::base_id,
        SCALE_STATISTICS_REPORT = 0x0035 | info<scale>::base_id,
        DATA_WEIGHT = 0x0040 | info<scale>::base_id,
        DATA_SCALING = 0x0041 | info<scale>::base_id,
        WEIGHT_UNIT = 0x0050 | info<scale>::base_id,
        WEIGHT_UNIT_MILLIGRAM = 0x0051 | info<scale>::base_id,
        WEIGHT_UNIT_GRAM = 0x0052 | info<scale>::base_id,
        WEIGHT_UNIT_KILOGRAM = 0x0053 | info<scale>::base_id,
        WEIGHT_UNIT_CARATS = 0x0054 | info<scale>::base_id,
        WEIGHT_UNIT_TAELS = 0x0055 | info<scale>::base_id,
        WEIGHT_UNIT_GRAINS = 0x0056 | info<scale>::base_id,
        WEIGHT_UNIT_PENNYWEIGHTS = 0x0057 | info<scale>::base_id,
        WEIGHT_UNIT_METRIC_TON = 0x0058 | info<scale>::base_id,
        WEIGHT_UNIT_AVOIR_TON = 0x0059 | info<scale>::base_id,
        WEIGHT_UNIT_TROY_OUNCE = 0x005a | info<scale>::base_id,
        WEIGHT_UNIT_OUNCE = 0x005b | info<scale>::base_id,
        WEIGHT_UNIT_POUND = 0x005c | info<scale>::base_id,
        CALIBRATION_COUNT = 0x0060 | info<scale>::base_id,
        RE_ZERO_COUNT = 0x0061 | info<scale>::base_id,
        SCALE_STATUS = 0x0070 | info<scale>::base_id,
        SCALE_STATUS_FAULT = 0x0071 | info<scale>::base_id,
        SCALE_STATUS_STABLE_AT_CENTER_OF_ZERO = 0x0072 | info<scale>::base_id,
        SCALE_STATUS_IN_MOTION = 0x0073 | info<scale>::base_id,
        SCALE_STATUS_WEIGHT_STABLE = 0x0074 | info<scale>::base_id,
        SCALE_STATUS_UNDER_ZERO = 0x0075 | info<scale>::base_id,
        SCALE_STATUS_OVER_WEIGHT_LIMIT = 0x0076 | info<scale>::base_id,
        SCALE_STATUS_REQUIRES_CALIBRATION = 0x0077 | info<scale>::base_id,
        SCALE_STATUS_REQUIRES_REZEROING = 0x0078 | info<scale>::base_id,
        ZERO_SCALE = 0x0080 | info<scale>::base_id,
        ENFORCED_ZERO_RETURN = 0x0081 | info<scale>::base_id,
    };
}

#endif // __HID_PAGE_SCALE_H_

