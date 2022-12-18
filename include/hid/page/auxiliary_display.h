#ifndef __HID_PAGE_AUXILIARY_DISPLAY_H_
#define __HID_PAGE_AUXILIARY_DISPLAY_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class auxiliary_display : usage_id_type;
    template<>
    struct info<auxiliary_display>
    {
        constexpr static usage_id_type base_id = 0x00140000;
        constexpr static usage_id_type max_usage = 0x00ff | base_id;
        constexpr static const char* name = "Auxiliary Display";
    };
    enum class auxiliary_display : usage_id_type
    {
        ALPHANUMERIC_DISPLAY = 0x0001 | info<auxiliary_display>::base_id,
        AUXILIARY_DISPLAY = 0x0002 | info<auxiliary_display>::base_id,
        DISPLAY_ATTRIBUTES_REPORT = 0x0020 | info<auxiliary_display>::base_id,
        ASCII_CHARACTER_SET = 0x0021 | info<auxiliary_display>::base_id,
        DATA_READ_BACK = 0x0022 | info<auxiliary_display>::base_id,
        FONT_READ_BACK = 0x0023 | info<auxiliary_display>::base_id,
        DISPLAY_CONTROL_REPORT = 0x0024 | info<auxiliary_display>::base_id,
        CLEAR_DISPLAY = 0x0025 | info<auxiliary_display>::base_id,
        DISPLAY_ENABLE = 0x0026 | info<auxiliary_display>::base_id,
        SCREEN_SAVER_DELAY = 0x0027 | info<auxiliary_display>::base_id,
        SCREEN_SAVER_ENABLE = 0x0028 | info<auxiliary_display>::base_id,
        VERTICAL_SCROLL = 0x0029 | info<auxiliary_display>::base_id,
        HORIZONTAL_SCROLL = 0x002a | info<auxiliary_display>::base_id,
        CHARACTER_REPORT = 0x002b | info<auxiliary_display>::base_id,
        DISPLAY_DATA = 0x002c | info<auxiliary_display>::base_id,
        DISPLAY_STATUS = 0x002d | info<auxiliary_display>::base_id,
        STAT_NOT_READY = 0x002e | info<auxiliary_display>::base_id,
        STAT_READY = 0x002f | info<auxiliary_display>::base_id,
        ERR_NOT_A_LOADABLE_CHARACTER = 0x0030 | info<auxiliary_display>::base_id,
        ERR_FONT_DATA_CANNOT_BE_READ = 0x0031 | info<auxiliary_display>::base_id,
        CURSOR_POSITION_REPORT = 0x0032 | info<auxiliary_display>::base_id,
        ROW = 0x0033 | info<auxiliary_display>::base_id,
        COLUMN = 0x0034 | info<auxiliary_display>::base_id,
        ROWS = 0x0035 | info<auxiliary_display>::base_id,
        COLUMNS = 0x0036 | info<auxiliary_display>::base_id,
        CURSOR_PIXEL_POSITIONING = 0x0037 | info<auxiliary_display>::base_id,
        CURSOR_MODE = 0x0038 | info<auxiliary_display>::base_id,
        CURSOR_ENABLE = 0x0039 | info<auxiliary_display>::base_id,
        CURSOR_BLINK = 0x003a | info<auxiliary_display>::base_id,
        FONT_REPORT = 0x003b | info<auxiliary_display>::base_id,
        FONT_DATA = 0x003c | info<auxiliary_display>::base_id,
        CHARACTER_WIDTH = 0x003d | info<auxiliary_display>::base_id,
        CHARACTER_HEIGHT = 0x003e | info<auxiliary_display>::base_id,
        CHARACTER_SPACING_HORIZONTAL = 0x003f | info<auxiliary_display>::base_id,
        CHARACTER_SPACING_VERTICAL = 0x0040 | info<auxiliary_display>::base_id,
        UNICODE_CHARACTER_SET = 0x0041 | info<auxiliary_display>::base_id,
        FONT_7_SEGMENT = 0x0042 | info<auxiliary_display>::base_id,
        _7_SEGMENT_DIRECT_MAP = 0x0043 | info<auxiliary_display>::base_id,
        FONT_14_SEGMENT = 0x0044 | info<auxiliary_display>::base_id,
        _14_SEGMENT_DIRECT_MAP = 0x0045 | info<auxiliary_display>::base_id,
        DISPLAY_BRIGHTNESS = 0x0046 | info<auxiliary_display>::base_id,
        DISPLAY_CONTRAST = 0x0047 | info<auxiliary_display>::base_id,
        CHARACTER_ATTRIBUTE = 0x0048 | info<auxiliary_display>::base_id,
        ATTRIBUTE_READBACK = 0x0049 | info<auxiliary_display>::base_id,
        ATTRIBUTE_DATA = 0x004a | info<auxiliary_display>::base_id,
        CHAR_ATTR_ENHANCE = 0x004b | info<auxiliary_display>::base_id,
        CHAR_ATTR_UNDERLINE = 0x004c | info<auxiliary_display>::base_id,
        CHAR_ATTR_BLINK = 0x004d | info<auxiliary_display>::base_id,
        BITMAP_SIZE_X = 0x0080 | info<auxiliary_display>::base_id,
        BITMAP_SIZE_Y = 0x0081 | info<auxiliary_display>::base_id,
        MAX_BLIT_SIZE = 0x0082 | info<auxiliary_display>::base_id,
        BIT_DEPTH_FORMAT = 0x0083 | info<auxiliary_display>::base_id,
        DISPLAY_ORIENTATION = 0x0084 | info<auxiliary_display>::base_id,
        PALETTE_REPORT = 0x0085 | info<auxiliary_display>::base_id,
        PALETTE_DATA_SIZE = 0x0086 | info<auxiliary_display>::base_id,
        PALETTE_DATA_OFFSET = 0x0087 | info<auxiliary_display>::base_id,
        PALETTE_DATA = 0x0088 | info<auxiliary_display>::base_id,
        BLIT_REPORT = 0x008a | info<auxiliary_display>::base_id,
        BLIT_RECTANGLE_X1 = 0x008b | info<auxiliary_display>::base_id,
        BLIT_RECTANGLE_Y1 = 0x008c | info<auxiliary_display>::base_id,
        BLIT_RECTANGLE_X2 = 0x008d | info<auxiliary_display>::base_id,
        BLIT_RECTANGLE_Y2 = 0x008e | info<auxiliary_display>::base_id,
        BLIT_DATA = 0x008f | info<auxiliary_display>::base_id,
        SOFT_BUTTON = 0x0090 | info<auxiliary_display>::base_id,
        SOFT_BUTTON_ID = 0x0091 | info<auxiliary_display>::base_id,
        SOFT_BUTTON_SIDE = 0x0092 | info<auxiliary_display>::base_id,
        SOFT_BUTTON_OFFSET_1 = 0x0093 | info<auxiliary_display>::base_id,
        SOFT_BUTTON_OFFSET_2 = 0x0094 | info<auxiliary_display>::base_id,
        SOFT_BUTTON_REPORT = 0x0095 | info<auxiliary_display>::base_id,
        SOFT_KEYS = 0x00c2 | info<auxiliary_display>::base_id,
        DISPLAY_DATA_EXTENSIONS = 0x00cc | info<auxiliary_display>::base_id,
        CHARACTER_MAPPING = 0x00cf | info<auxiliary_display>::base_id,
        UNICODE_EQUIVALENT = 0x00dd | info<auxiliary_display>::base_id,
        CHARACTER_PAGE_MAPPING = 0x00df | info<auxiliary_display>::base_id,
        REQUEST_REPORT = 0x00ff | info<auxiliary_display>::base_id,
    };
}

#endif // __HID_PAGE_AUXILIARY_DISPLAY_H_

