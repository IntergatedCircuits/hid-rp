#ifndef __HID_PAGE_MAGNETIC_STRIPE_READING_DEVICES_H_
#define __HID_PAGE_MAGNETIC_STRIPE_READING_DEVICES_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class magnetic_stripe_reading_devices : usage_id_type;
    template<>
    struct info<magnetic_stripe_reading_devices>
    {
        constexpr static usage_id_type base_id = 0x008e0000;
        constexpr static usage_id_type max_usage = 0x0024 | base_id;
        constexpr static const char* name = "Magnetic Stripe Reading (MSR) Devices";
    };
    enum class magnetic_stripe_reading_devices : usage_id_type
    {
        MSR_DEVICE_READ_ONLY = 0x0001 | info<magnetic_stripe_reading_devices>::base_id,
        TRACK_1_LENGTH = 0x0011 | info<magnetic_stripe_reading_devices>::base_id,
        TRACK_2_LENGTH = 0x0012 | info<magnetic_stripe_reading_devices>::base_id,
        TRACK_3_LENGTH = 0x0013 | info<magnetic_stripe_reading_devices>::base_id,
        TRACK_JIS_LENGTH = 0x0014 | info<magnetic_stripe_reading_devices>::base_id,
        TRACK_DATA = 0x0020 | info<magnetic_stripe_reading_devices>::base_id,
        TRACK_1_DATA = 0x0021 | info<magnetic_stripe_reading_devices>::base_id,
        TRACK_2_DATA = 0x0022 | info<magnetic_stripe_reading_devices>::base_id,
        TRACK_3_DATA = 0x0023 | info<magnetic_stripe_reading_devices>::base_id,
        TRACK_JIS_DATA = 0x0024 | info<magnetic_stripe_reading_devices>::base_id,
    };
}

#endif // __HID_PAGE_MAGNETIC_STRIPE_READING_DEVICES_H_

