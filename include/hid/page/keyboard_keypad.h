#ifndef __HID_PAGE_KEYBOARD_KEYPAD_H_
#define __HID_PAGE_KEYBOARD_KEYPAD_H_

#include "hid/usage.h"

namespace hid::page
{
    enum class keyboard_keypad : usage_id_type;
    template<>
    struct info<keyboard_keypad>
    {
        constexpr static usage_id_type base_id = 0x00070000;
        constexpr static usage_id_type max_usage = 0x00e7 | base_id;
        constexpr static const char* name = "Keyboard/Keypad";
    };
    enum class keyboard_keypad : usage_id_type
    {
        ERRORROLLOVER = 0x0001 | info<keyboard_keypad>::base_id,
        POSTFAIL = 0x0002 | info<keyboard_keypad>::base_id,
        ERRORUNDEFINED = 0x0003 | info<keyboard_keypad>::base_id,
        A = 0x0004 | info<keyboard_keypad>::base_id,
        B = 0x0005 | info<keyboard_keypad>::base_id,
        C = 0x0006 | info<keyboard_keypad>::base_id,
        D = 0x0007 | info<keyboard_keypad>::base_id,
        E = 0x0008 | info<keyboard_keypad>::base_id,
        F = 0x0009 | info<keyboard_keypad>::base_id,
        G = 0x000a | info<keyboard_keypad>::base_id,
        H = 0x000b | info<keyboard_keypad>::base_id,
        I = 0x000c | info<keyboard_keypad>::base_id,
        J = 0x000d | info<keyboard_keypad>::base_id,
        K = 0x000e | info<keyboard_keypad>::base_id,
        L = 0x000f | info<keyboard_keypad>::base_id,
        M = 0x0010 | info<keyboard_keypad>::base_id,
        N = 0x0011 | info<keyboard_keypad>::base_id,
        O = 0x0012 | info<keyboard_keypad>::base_id,
        P = 0x0013 | info<keyboard_keypad>::base_id,
        Q = 0x0014 | info<keyboard_keypad>::base_id,
        R = 0x0015 | info<keyboard_keypad>::base_id,
        S = 0x0016 | info<keyboard_keypad>::base_id,
        T = 0x0017 | info<keyboard_keypad>::base_id,
        U = 0x0018 | info<keyboard_keypad>::base_id,
        V = 0x0019 | info<keyboard_keypad>::base_id,
        W = 0x001a | info<keyboard_keypad>::base_id,
        X = 0x001b | info<keyboard_keypad>::base_id,
        Y = 0x001c | info<keyboard_keypad>::base_id,
        Z = 0x001d | info<keyboard_keypad>::base_id,
        _1_EXCLAMATION_MARK = 0x001e | info<keyboard_keypad>::base_id,
        _2_COMMERCIAL_AT = 0x001f | info<keyboard_keypad>::base_id,
        _3_NUMBER_SIGN = 0x0020 | info<keyboard_keypad>::base_id,
        _4_DOLLAR_SIGN = 0x0021 | info<keyboard_keypad>::base_id,
        _5_PERCENT_SIGN = 0x0022 | info<keyboard_keypad>::base_id,
        _6_CIRCUMFLEX_ACCENT = 0x0023 | info<keyboard_keypad>::base_id,
        _7_AMPERSAND = 0x0024 | info<keyboard_keypad>::base_id,
        _8_ASTERISK = 0x0025 | info<keyboard_keypad>::base_id,
        _9_LEFT_PARENTHESIS = 0x0026 | info<keyboard_keypad>::base_id,
        _0_RIGHT_PARENTHESIS = 0x0027 | info<keyboard_keypad>::base_id,
        ENTER = 0x0028 | info<keyboard_keypad>::base_id,
        ESC = 0x0029 | info<keyboard_keypad>::base_id,
        BACKSPACE = 0x002a | info<keyboard_keypad>::base_id,
        TAB = 0x002b | info<keyboard_keypad>::base_id,
        SPACE = 0x002c | info<keyboard_keypad>::base_id,
        HYPHEN_MINUS_LOW_LINE = 0x002d | info<keyboard_keypad>::base_id,
        EQUALS_SIGN_PLUS_SIGN = 0x002e | info<keyboard_keypad>::base_id,
        LEFT_SQUARE_BRACKET_LEFT_CURLY_BRACKET = 0x002f | info<keyboard_keypad>::base_id,
        RIGHT_SQUARE_BRACKET_RIGHT_CURLY_BRACKET = 0x0030 | info<keyboard_keypad>::base_id,
        REVERSE_SOLIDUS_VERTICAL_LINE = 0x0031 | info<keyboard_keypad>::base_id,
        NUMBER_SIGN_TILDE = 0x0032 | info<keyboard_keypad>::base_id,
        SEMICOLON_COLON = 0x0033 | info<keyboard_keypad>::base_id,
        APOSTROPHE_QUOTATION_MARK = 0x0034 | info<keyboard_keypad>::base_id,
        GRAVE_ACCENT_ACUTE_ACCENT = 0x0035 | info<keyboard_keypad>::base_id,
        COMMA_LESS_THAN_SIGN = 0x0036 | info<keyboard_keypad>::base_id,
        FULL_STOP_GREATER_THAN_SIGN = 0x0037 | info<keyboard_keypad>::base_id,
        SOLIDUS_QUESTION_MARK = 0x0038 | info<keyboard_keypad>::base_id,
        CAPSLOCK = 0x0039 | info<keyboard_keypad>::base_id,
        F1 = 0x003a | info<keyboard_keypad>::base_id,
        F2 = 0x003b | info<keyboard_keypad>::base_id,
        F3 = 0x003c | info<keyboard_keypad>::base_id,
        F4 = 0x003d | info<keyboard_keypad>::base_id,
        F5 = 0x003e | info<keyboard_keypad>::base_id,
        F6 = 0x003f | info<keyboard_keypad>::base_id,
        F7 = 0x0040 | info<keyboard_keypad>::base_id,
        F8 = 0x0041 | info<keyboard_keypad>::base_id,
        F9 = 0x0042 | info<keyboard_keypad>::base_id,
        F10 = 0x0043 | info<keyboard_keypad>::base_id,
        F11 = 0x0044 | info<keyboard_keypad>::base_id,
        F12 = 0x0045 | info<keyboard_keypad>::base_id,
        PRINTSCREEN_SYSRQ = 0x0046 | info<keyboard_keypad>::base_id,
        SCROLLLOCK = 0x0047 | info<keyboard_keypad>::base_id,
        PAUSE = 0x0048 | info<keyboard_keypad>::base_id,
        INSERT = 0x0049 | info<keyboard_keypad>::base_id,
        HOME = 0x004a | info<keyboard_keypad>::base_id,
        PAGEUP = 0x004b | info<keyboard_keypad>::base_id,
        DELETE = 0x004c | info<keyboard_keypad>::base_id,
        END = 0x004d | info<keyboard_keypad>::base_id,
        PAGEDOWN = 0x004e | info<keyboard_keypad>::base_id,
        RIGHTARROW = 0x004f | info<keyboard_keypad>::base_id,
        LEFTARROW = 0x0050 | info<keyboard_keypad>::base_id,
        DOWNARROW = 0x0051 | info<keyboard_keypad>::base_id,
        UPARROW = 0x0052 | info<keyboard_keypad>::base_id,
        NUMLOCK_CLEAR = 0x0053 | info<keyboard_keypad>::base_id,
        KEYPAD_SOLIDUS = 0x0054 | info<keyboard_keypad>::base_id,
        KEYPAD_ASTERISK = 0x0055 | info<keyboard_keypad>::base_id,
        KEYPAD_HYPHEN_MINUS = 0x0056 | info<keyboard_keypad>::base_id,
        KEYPAD_PLUS_SIGN = 0x0057 | info<keyboard_keypad>::base_id,
        KEYPAD_ENTER = 0x0058 | info<keyboard_keypad>::base_id,
        KEYPAD_1 = 0x0059 | info<keyboard_keypad>::base_id,
        KEYPAD_2 = 0x005a | info<keyboard_keypad>::base_id,
        KEYPAD_3 = 0x005b | info<keyboard_keypad>::base_id,
        KEYPAD_4 = 0x005c | info<keyboard_keypad>::base_id,
        KEYPAD_5 = 0x005d | info<keyboard_keypad>::base_id,
        KEYPAD_6 = 0x005e | info<keyboard_keypad>::base_id,
        KEYPAD_7 = 0x005f | info<keyboard_keypad>::base_id,
        KEYPAD_8 = 0x0060 | info<keyboard_keypad>::base_id,
        KEYPAD_9 = 0x0061 | info<keyboard_keypad>::base_id,
        KEYPAD_0 = 0x0062 | info<keyboard_keypad>::base_id,
        KEYPAD_FULL_STOP = 0x0063 | info<keyboard_keypad>::base_id,
        NON_US_REVERSE_SOLIDUS_VERTICAL_LINE = 0x0064 | info<keyboard_keypad>::base_id,
        APPLICATION = 0x0065 | info<keyboard_keypad>::base_id,
        POWER = 0x0066 | info<keyboard_keypad>::base_id,
        KEYPAD_EQUALS_SIGN = 0x0067 | info<keyboard_keypad>::base_id,
        F13 = 0x0068 | info<keyboard_keypad>::base_id,
        F14 = 0x0069 | info<keyboard_keypad>::base_id,
        F15 = 0x006a | info<keyboard_keypad>::base_id,
        F16 = 0x006b | info<keyboard_keypad>::base_id,
        F17 = 0x006c | info<keyboard_keypad>::base_id,
        F18 = 0x006d | info<keyboard_keypad>::base_id,
        F19 = 0x006e | info<keyboard_keypad>::base_id,
        F20 = 0x006f | info<keyboard_keypad>::base_id,
        F21 = 0x0070 | info<keyboard_keypad>::base_id,
        F22 = 0x0071 | info<keyboard_keypad>::base_id,
        F23 = 0x0072 | info<keyboard_keypad>::base_id,
        F24 = 0x0073 | info<keyboard_keypad>::base_id,
        EXECUTE = 0x0074 | info<keyboard_keypad>::base_id,
        HELP = 0x0075 | info<keyboard_keypad>::base_id,
        MENU = 0x0076 | info<keyboard_keypad>::base_id,
        SELECT = 0x0077 | info<keyboard_keypad>::base_id,
        STOP = 0x0078 | info<keyboard_keypad>::base_id,
        AGAIN = 0x0079 | info<keyboard_keypad>::base_id,
        UNDO = 0x007a | info<keyboard_keypad>::base_id,
        CUT = 0x007b | info<keyboard_keypad>::base_id,
        COPY = 0x007c | info<keyboard_keypad>::base_id,
        PASTE = 0x007d | info<keyboard_keypad>::base_id,
        FIND = 0x007e | info<keyboard_keypad>::base_id,
        MUTE = 0x007f | info<keyboard_keypad>::base_id,
        VOLUMEUP = 0x0080 | info<keyboard_keypad>::base_id,
        VOLUMEDOWN = 0x0081 | info<keyboard_keypad>::base_id,
        LOCKINGCAPSLOCK = 0x0082 | info<keyboard_keypad>::base_id,
        LOCKINGNUMLOCK = 0x0083 | info<keyboard_keypad>::base_id,
        LOCKINGSCROLLLOCK = 0x0084 | info<keyboard_keypad>::base_id,
        KEYPAD_COMMA = 0x0085 | info<keyboard_keypad>::base_id,
        KEYPAD_EQUALS_SIGN_EQUALS_SIGN = 0x0086 | info<keyboard_keypad>::base_id,
        INTERNATIONAL1 = 0x0087 | info<keyboard_keypad>::base_id,
        INTERNATIONAL2 = 0x0088 | info<keyboard_keypad>::base_id,
        INTERNATIONAL3 = 0x0089 | info<keyboard_keypad>::base_id,
        INTERNATIONAL4 = 0x008a | info<keyboard_keypad>::base_id,
        INTERNATIONAL5 = 0x008b | info<keyboard_keypad>::base_id,
        INTERNATIONAL6 = 0x008c | info<keyboard_keypad>::base_id,
        INTERNATIONAL7 = 0x008d | info<keyboard_keypad>::base_id,
        INTERNATIONAL8 = 0x008e | info<keyboard_keypad>::base_id,
        INTERNATIONAL9 = 0x008f | info<keyboard_keypad>::base_id,
        LANG1 = 0x0090 | info<keyboard_keypad>::base_id,
        LANG2 = 0x0091 | info<keyboard_keypad>::base_id,
        LANG3 = 0x0092 | info<keyboard_keypad>::base_id,
        LANG4 = 0x0093 | info<keyboard_keypad>::base_id,
        LANG5 = 0x0094 | info<keyboard_keypad>::base_id,
        LANG6 = 0x0095 | info<keyboard_keypad>::base_id,
        LANG7 = 0x0096 | info<keyboard_keypad>::base_id,
        LANG8 = 0x0097 | info<keyboard_keypad>::base_id,
        LANG9 = 0x0098 | info<keyboard_keypad>::base_id,
        ALTERNATE_ERASE = 0x0099 | info<keyboard_keypad>::base_id,
        SYSREQ_ATTENTION = 0x009a | info<keyboard_keypad>::base_id,
        CANCEL = 0x009b | info<keyboard_keypad>::base_id,
        CLEAR = 0x009c | info<keyboard_keypad>::base_id,
        PRIOR = 0x009d | info<keyboard_keypad>::base_id,
        RETURN = 0x009e | info<keyboard_keypad>::base_id,
        SEPARATOR = 0x009f | info<keyboard_keypad>::base_id,
        OUT = 0x00a0 | info<keyboard_keypad>::base_id,
        OPER = 0x00a1 | info<keyboard_keypad>::base_id,
        CLEAR_AGAIN = 0x00a2 | info<keyboard_keypad>::base_id,
        CRSEL_PROPS = 0x00a3 | info<keyboard_keypad>::base_id,
        EXSEL = 0x00a4 | info<keyboard_keypad>::base_id,
        KEYPAD_00 = 0x00b0 | info<keyboard_keypad>::base_id,
        KEYPAD_000 = 0x00b1 | info<keyboard_keypad>::base_id,
        _1000SSEPARATOR = 0x00b2 | info<keyboard_keypad>::base_id,
        DECIMALSEPARATOR = 0x00b3 | info<keyboard_keypad>::base_id,
        CURRENCYUNIT = 0x00b4 | info<keyboard_keypad>::base_id,
        CURRENCYSUBUNIT = 0x00b5 | info<keyboard_keypad>::base_id,
        KEYPAD_LEFT_PARENTHESIS = 0x00b6 | info<keyboard_keypad>::base_id,
        KEYPAD_RIGHT_PARENTHESIS = 0x00b7 | info<keyboard_keypad>::base_id,
        KEYPAD_LEFT_CURLY_BRACKET = 0x00b8 | info<keyboard_keypad>::base_id,
        KEYPAD_RIGHT_CURLY_BRACKET = 0x00b9 | info<keyboard_keypad>::base_id,
        KEYPAD_TAB = 0x00ba | info<keyboard_keypad>::base_id,
        KEYPAD_BACKSPACE = 0x00bb | info<keyboard_keypad>::base_id,
        KEYPAD_A = 0x00bc | info<keyboard_keypad>::base_id,
        KEYPAD_B = 0x00bd | info<keyboard_keypad>::base_id,
        KEYPAD_C = 0x00be | info<keyboard_keypad>::base_id,
        KEYPAD_D = 0x00bf | info<keyboard_keypad>::base_id,
        KEYPAD_E = 0x00c0 | info<keyboard_keypad>::base_id,
        KEYPAD_F = 0x00c1 | info<keyboard_keypad>::base_id,
        KEYPAD_XOR = 0x00c2 | info<keyboard_keypad>::base_id,
        KEYPAD_CIRCUMFLEX_ACCENT = 0x00c3 | info<keyboard_keypad>::base_id,
        KEYPAD_PERCENT_SIGN = 0x00c4 | info<keyboard_keypad>::base_id,
        KEYPAD_LESS_THAN_SIGN = 0x00c5 | info<keyboard_keypad>::base_id,
        KEYPAD_GREATER_THAN_SIGN = 0x00c6 | info<keyboard_keypad>::base_id,
        KEYPAD_AMPERSAND = 0x00c7 | info<keyboard_keypad>::base_id,
        KEYPAD_AMPERSAND_AMPERSAND = 0x00c8 | info<keyboard_keypad>::base_id,
        KEYPAD_VERTICAL_LINE = 0x00c9 | info<keyboard_keypad>::base_id,
        KEYPAD_VERTICAL_LINE_VERTICAL_LINE = 0x00ca | info<keyboard_keypad>::base_id,
        KEYPAD_COLON = 0x00cb | info<keyboard_keypad>::base_id,
        KEYPAD_NUMBER_SIGN = 0x00cc | info<keyboard_keypad>::base_id,
        KEYPAD_SPACE = 0x00cd | info<keyboard_keypad>::base_id,
        KEYPAD_COMMERCIAL_AT = 0x00ce | info<keyboard_keypad>::base_id,
        KEYPAD_EXCLAMATION_MARK = 0x00cf | info<keyboard_keypad>::base_id,
        KEYPAD_MEMORYSTORE = 0x00d0 | info<keyboard_keypad>::base_id,
        KEYPAD_MEMORYRECALL = 0x00d1 | info<keyboard_keypad>::base_id,
        KEYPAD_MEMORYCLEAR = 0x00d2 | info<keyboard_keypad>::base_id,
        KEYPAD_MEMORYADD = 0x00d3 | info<keyboard_keypad>::base_id,
        KEYPAD_MEMORYSUBTRACT = 0x00d4 | info<keyboard_keypad>::base_id,
        KEYPAD_MEMORYMULTIPLY = 0x00d5 | info<keyboard_keypad>::base_id,
        KEYPAD_MEMORYDIVIDE = 0x00d6 | info<keyboard_keypad>::base_id,
        KEYPAD_PLUS_SIGN_SOLIDUS_HYPHEN_MINUS = 0x00d7 | info<keyboard_keypad>::base_id,
        KEYPAD_CLEAR = 0x00d8 | info<keyboard_keypad>::base_id,
        KEYPAD_CLEARENTRY = 0x00d9 | info<keyboard_keypad>::base_id,
        KEYPAD_BINARY = 0x00da | info<keyboard_keypad>::base_id,
        KEYPAD_OCTAL = 0x00db | info<keyboard_keypad>::base_id,
        KEYPAD_DECIMAL = 0x00dc | info<keyboard_keypad>::base_id,
        KEYPAD_HEXADECIMAL = 0x00dd | info<keyboard_keypad>::base_id,
        LEFTCTRL = 0x00e0 | info<keyboard_keypad>::base_id,
        LEFTSHIFT = 0x00e1 | info<keyboard_keypad>::base_id,
        LEFTALT = 0x00e2 | info<keyboard_keypad>::base_id,
        LEFTGUI = 0x00e3 | info<keyboard_keypad>::base_id,
        RIGHTCTRL = 0x00e4 | info<keyboard_keypad>::base_id,
        RIGHTSHIFT = 0x00e5 | info<keyboard_keypad>::base_id,
        RIGHTALT = 0x00e6 | info<keyboard_keypad>::base_id,
        RIGHTGUI = 0x00e7 | info<keyboard_keypad>::base_id,
    };
}

#endif // __HID_PAGE_KEYBOARD_KEYPAD_H_

