#ifndef __HID_PAGE_VESA_VIRTUAL_H_
#define __HID_PAGE_VESA_VIRTUAL_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class vesa_virtual : usage_id_type;
    template<>
    struct info<vesa_virtual>
    {
        constexpr static usage_id_type base_id = 0x00820000;
        constexpr static usage_id_type max_usage = 0x00d4 | base_id;
        constexpr static const char* name = "VESA Virtual Controls";
    };
    enum class vesa_virtual : usage_id_type
    {
        DEGAUSS = 0x0001 | info<vesa_virtual>::base_id,
        BRIGHTNESS = 0x0010 | info<vesa_virtual>::base_id,
        CONTRAST = 0x0012 | info<vesa_virtual>::base_id,
        RED_VIDEO_GAIN = 0x0016 | info<vesa_virtual>::base_id,
        GREEN_VIDEO_GAIN = 0x0018 | info<vesa_virtual>::base_id,
        BLUE_VIDEO_GAIN = 0x001a | info<vesa_virtual>::base_id,
        FOCUS = 0x001c | info<vesa_virtual>::base_id,
        HORIZONTAL_POSITION = 0x0020 | info<vesa_virtual>::base_id,
        HORIZONTAL_SIZE = 0x0022 | info<vesa_virtual>::base_id,
        HORIZONTAL_PINCUSHION = 0x0024 | info<vesa_virtual>::base_id,
        HORIZONTAL_PINCUSHION_BALANCE = 0x0026 | info<vesa_virtual>::base_id,
        HORIZONTAL_MISCONVERGENCE = 0x0028 | info<vesa_virtual>::base_id,
        HORIZONTAL_LINEARITY = 0x002a | info<vesa_virtual>::base_id,
        HORIZONTAL_LINEARITY_BALANCE = 0x002c | info<vesa_virtual>::base_id,
        VERTICAL_POSITION = 0x0030 | info<vesa_virtual>::base_id,
        VERTICAL_SIZE = 0x0032 | info<vesa_virtual>::base_id,
        VERTICAL_PINCUSHION = 0x0034 | info<vesa_virtual>::base_id,
        VERTICAL_PINCUSHION_BALANCE = 0x0036 | info<vesa_virtual>::base_id,
        VERTICAL_MISCONVERGENCE = 0x0038 | info<vesa_virtual>::base_id,
        VERTICAL_LINEARITY = 0x003a | info<vesa_virtual>::base_id,
        VERTICAL_LINEARITY_BALANCE = 0x003c | info<vesa_virtual>::base_id,
        PARALLELOGRAM_DISTORTION_KEY_BALANCE = 0x0040 | info<vesa_virtual>::base_id,
        TRAPEZOIDAL_DISTORTION_KEY = 0x0042 | info<vesa_virtual>::base_id,
        TILT_ROTATION = 0x0044 | info<vesa_virtual>::base_id,
        TOP_CORNER_DISTORTION_CONTROL = 0x0046 | info<vesa_virtual>::base_id,
        TOP_CORNER_DISTORTION_BALANCE = 0x0048 | info<vesa_virtual>::base_id,
        BOTTOM_CORNER_DISTORTION_CONTROL = 0x004a | info<vesa_virtual>::base_id,
        BOTTOM_CORNER_DISTORTION_BALANCE = 0x004c | info<vesa_virtual>::base_id,
        HORIZONTAL_MOIRE = 0x0056 | info<vesa_virtual>::base_id,
        VERTICAL_MOIRE = 0x0058 | info<vesa_virtual>::base_id,
        INPUT_LEVEL_SELECT = 0x005e | info<vesa_virtual>::base_id,
        INPUT_SOURCE_SELECT = 0x0060 | info<vesa_virtual>::base_id,
        RED_VIDEO_BLACK_LEVEL = 0x006c | info<vesa_virtual>::base_id,
        GREEN_VIDEO_BLACK_LEVEL = 0x006e | info<vesa_virtual>::base_id,
        BLUE_VIDEO_BLACK_LEVEL = 0x0070 | info<vesa_virtual>::base_id,
        AUTO_SIZE_CENTER = 0x00a2 | info<vesa_virtual>::base_id,
        POLARITY_HORIZONTAL_SYNCHRONIZATION = 0x00a4 | info<vesa_virtual>::base_id,
        POLARITY_VERTICAL_SYNCHRONIZATION = 0x00a6 | info<vesa_virtual>::base_id,
        SYNCHRONIZATION_TYPE = 0x00a8 | info<vesa_virtual>::base_id,
        SCREEN_ORIENTATION = 0x00aa | info<vesa_virtual>::base_id,
        HORIZONTAL_FREQUENCY = 0x00ac | info<vesa_virtual>::base_id,
        VERTICAL_FREQUENCY = 0x00ae | info<vesa_virtual>::base_id,
        SETTINGS = 0x00b0 | info<vesa_virtual>::base_id,
        ON_SCREEN_DISPLAY = 0x00ca | info<vesa_virtual>::base_id,
        STEREOMODE = 0x00d4 | info<vesa_virtual>::base_id,
    };
}

#endif // __HID_PAGE_VESA_VIRTUAL_H_

