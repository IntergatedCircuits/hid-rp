#ifndef __HID_PAGE_FIDO_H_
#define __HID_PAGE_FIDO_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class fido : usage_id_type;
    template<>
    struct info<fido>
    {
        constexpr static usage_id_type base_id = 0xf1d00000;
        constexpr static usage_id_type max_usage = 0x0021 | base_id;
        constexpr static const char* name = "Fast IDentity Online Alliance";
    };
    enum class fido : usage_id_type
    {
        U2F_AUTHENTICATOR_DEVICE = 0x0001 | info<fido>::base_id,
        INPUT_REPORT_DATA = 0x0020 | info<fido>::base_id,
        OUTPUT_REPORT_DATA = 0x0021 | info<fido>::base_id,
    };
}

#endif // __HID_PAGE_FIDO_H_

