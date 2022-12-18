#ifndef __HID_PAGE_GAME_H_
#define __HID_PAGE_GAME_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class game : usage_id_type;
    template<>
    struct info<game>
    {
        constexpr static usage_id_type base_id = 0x00050000;
        constexpr static usage_id_type max_usage = 0x003a | base_id;
        constexpr static const char* name = "Game Controls";
    };
    enum class game : usage_id_type
    {
        _3D_GAME_CONTROLLER = 0x0001 | info<game>::base_id,
        PINBALL_DEVICE = 0x0002 | info<game>::base_id,
        GUN_DEVICE = 0x0003 | info<game>::base_id,
        POINT_OF_VIEW = 0x0020 | info<game>::base_id,
        TURN_RIGHT_LEFT = 0x0021 | info<game>::base_id,
        PITCH_RIGHT_LEFT = 0x0022 | info<game>::base_id,
        ROLL_RIGHT_LEFT = 0x0023 | info<game>::base_id,
        MOVE_RIGHT_LEFT = 0x0024 | info<game>::base_id,
        MOVE_FORWARD_BACKWARD = 0x0025 | info<game>::base_id,
        MOVE_UP_DOWN = 0x0026 | info<game>::base_id,
        LEAN_RIGHT_LEFT = 0x0027 | info<game>::base_id,
        LEAN_FORWARD_BACKWARD = 0x0028 | info<game>::base_id,
        HEIGHT_OF_POV = 0x0029 | info<game>::base_id,
        FLIPPER = 0x002a | info<game>::base_id,
        SECONDARY_FLIPPER = 0x002b | info<game>::base_id,
        BUMP = 0x002c | info<game>::base_id,
        NEW_GAME = 0x002d | info<game>::base_id,
        SHOOT_BALL = 0x002e | info<game>::base_id,
        PLAYER = 0x002f | info<game>::base_id,
        GUN_BOLT = 0x0030 | info<game>::base_id,
        GUN_CLIP = 0x0031 | info<game>::base_id,
        GUN_SELECTOR = 0x0032 | info<game>::base_id,
        GUN_SINGLE_SHOT = 0x0033 | info<game>::base_id,
        GUN_BURST = 0x0034 | info<game>::base_id,
        GUN_AUTOMATIC = 0x0035 | info<game>::base_id,
        GUN_SAFETY = 0x0036 | info<game>::base_id,
        GAMEPAD_FIRE_JUMP = 0x0037 | info<game>::base_id,
        GAMEPAD_TRIGGER = 0x0039 | info<game>::base_id,
        FORM_FITTING_GAMEPAD = 0x003a | info<game>::base_id,
    };
}

#endif // __HID_PAGE_GAME_H_

