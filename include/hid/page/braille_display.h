#ifndef __HID_PAGE_BRAILLE_DISPLAY_H_
#define __HID_PAGE_BRAILLE_DISPLAY_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class braille_display : usage_id_type;
    template<>
    struct info<braille_display>
    {
        constexpr static usage_id_type base_id = 0x00410000;
        constexpr static usage_id_type max_usage = 0x021e | base_id;
        constexpr static const char* name = "Braille Display";
    };
    enum class braille_display : usage_id_type
    {
        BRAILLE_DISPLAY = 0x0001 | info<braille_display>::base_id,
        BRAILLE_ROW = 0x0002 | info<braille_display>::base_id,
        _8_DOT_BRAILLE_CELL = 0x0003 | info<braille_display>::base_id,
        _6_DOT_BRAILLE_CELL = 0x0004 | info<braille_display>::base_id,
        NUMBER_OF_BRAILLE_CELLS = 0x0005 | info<braille_display>::base_id,
        SCREEN_READER_CONTROL = 0x0006 | info<braille_display>::base_id,
        SCREEN_READER_IDENTIFIER = 0x0007 | info<braille_display>::base_id,
        ROUTER_SET_1 = 0x00fa | info<braille_display>::base_id,
        ROUTER_SET_2 = 0x00fb | info<braille_display>::base_id,
        ROUTER_SET_3 = 0x00fc | info<braille_display>::base_id,
        BRAILLE_BUTTONS = 0x0100 | info<braille_display>::base_id,
        BRAILLE_KEYBOARD_DOT_1 = 0x0201 | info<braille_display>::base_id,
        BRAILLE_KEYBOARD_DOT_2 = 0x0202 | info<braille_display>::base_id,
        BRAILLE_KEYBOARD_DOT_3 = 0x0203 | info<braille_display>::base_id,
        BRAILLE_KEYBOARD_DOT_4 = 0x0204 | info<braille_display>::base_id,
        BRAILLE_KEYBOARD_DOT_5 = 0x0205 | info<braille_display>::base_id,
        BRAILLE_KEYBOARD_DOT_6 = 0x0206 | info<braille_display>::base_id,
        BRAILLE_KEYBOARD_DOT_7 = 0x0207 | info<braille_display>::base_id,
        BRAILLE_KEYBOARD_DOT_8 = 0x0208 | info<braille_display>::base_id,
        BRAILLE_KEYBOARD_SPACE = 0x0209 | info<braille_display>::base_id,
        BRAILLE_KEYBOARD_LEFT_SPACE = 0x020a | info<braille_display>::base_id,
        BRAILLE_KEYBOARD_RIGHT_SPACE = 0x020b | info<braille_display>::base_id,
        BRAILLE_FACE_CONTROLS = 0x020c | info<braille_display>::base_id,
        BRAILLE_LEFT_CONTROLS = 0x020d | info<braille_display>::base_id,
        BRAILLE_RIGHT_CONTROLS = 0x020e | info<braille_display>::base_id,
        BRAILLE_TOP_CONTROLS = 0x020f | info<braille_display>::base_id,
        BRAILLE_JOYSTICK_CENTER = 0x0210 | info<braille_display>::base_id,
        BRAILLE_JOYSTICK_UP = 0x0211 | info<braille_display>::base_id,
        BRAILLE_JOYSTICK_DOWN = 0x0212 | info<braille_display>::base_id,
        BRAILLE_JOYSTICK_LEFT = 0x0213 | info<braille_display>::base_id,
        BRAILLE_JOYSTICK_RIGHT = 0x0214 | info<braille_display>::base_id,
        BRAILLE_D_PAD_CENTER = 0x0215 | info<braille_display>::base_id,
        BRAILLE_D_PAD_UP = 0x0216 | info<braille_display>::base_id,
        BRAILLE_D_PAD_DOWN = 0x0217 | info<braille_display>::base_id,
        BRAILLE_D_PAD_LEFT = 0x0218 | info<braille_display>::base_id,
        BRAILLE_D_PAD_RIGHT = 0x0219 | info<braille_display>::base_id,
        BRAILLE_PAN_LEFT = 0x021a | info<braille_display>::base_id,
        BRAILLE_PAN_RIGHT = 0x021b | info<braille_display>::base_id,
        BRAILLE_ROCKER_UP = 0x021c | info<braille_display>::base_id,
        BRAILLE_ROCKER_DOWN = 0x021d | info<braille_display>::base_id,
        BRAILLE_ROCKER_PRESS = 0x021e | info<braille_display>::base_id,
    };
}

#endif // __HID_PAGE_BRAILLE_DISPLAY_H_

