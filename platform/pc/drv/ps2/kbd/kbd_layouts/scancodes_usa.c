#include <drv/ps2/kbd/kbd.h>

int const QWERTY_USA_NOSHIFT_VAL[] = {
     0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
    '9', '0', '-', '=', '\b', /* Backspace */
    '\t', /* Tab */
    'q', 'w', 'e', 'r', /* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', KBD_ENTER_PRESS_ID, /* Enter key */
    KBD_CONTROL_PRESS_ID, /* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
    '\'', '`',   KBD_LEFT_SHIFT_PRESS_ID, /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', /* 49 */
    'm', ',', '.','/',  KBD_RIGHT_SHIFT_PRESS_ID, /* Right shift */
    '*',
    0, /* Alt */
    ' ', /* Space bar */
    KBD_CAPS_PRESS_ID, /* Caps lock */
    0, /* 59 - F1 key ... > */
    0, 0, 0, 0, 0, 0, 0, 0,
    0, /* < ... F10 */
    0, /* 69 - Num lock*/
    0, /* Scroll Lock */
    KBD_HOME_KEY_ID, /* Home key */
    KBD_UP_KEY_ID, /* Up Arrow */
    0, /* Page Up */
    '-',
    KBD_LEFT_KEY_ID, /* Left Arrow */
    0,
    KBD_RIGHT_KEY_ID, /* Right Arrow */
    '+',
    KBD_END_KEY_ID, /* 79 - End key*/
    KBD_DOWN_KEY_ID, /* Down Arrow */
    0, /* Page Down */
    0, /* Insert Key */
    KBD_DELETE_KEY_ID, /* Delete Key */
    0, 0, 0,
    0, /* F11 Key */
    0, /* F12 Key */
    0, /* All other keys are undefined */
};

int const QWERTY_USA_SHIFT_VAL[] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', /* 9 */
    '(', ')', '_', '+', '\b', /* Backspace */
    '\t', /* Tab */
    'Q', 'W', 'E', 'R', /* 19 */
    'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', KBD_ENTER_PRESS_ID, /* Enter key */
    KBD_CONTROL_PRESS_ID, /* 29   - Control */
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K' ,'L', ':', /* 39 */
    '\"' , '~',   KBD_LEFT_SHIFT_PRESS_ID, /* Left shift */
    '|', 'Z', 'X', 'C', 'V', 'B', 'N', /* 49 */
    'M', '<', '>', '?', KBD_RIGHT_SHIFT_PRESS_ID, /* Right shift */
    '*',
    0, /* Alt */
    ' ', /* Space bar */
    KBD_CAPS_PRESS_ID, /* Caps lock */
    0, /* 59 - F1 key ... > */
    0, 0, 0, 0, 0, 0, 0, 0,
    0, /* < ... F10 */
    0, /* 69 - Num lock*/
    0, /* Scroll Lock */
    0, /* Home key */
    KBD_UP_KEY_ID, /* Up Arrow */
    0, /* Page Up */
    '-',
    KBD_LEFT_KEY_ID, /* Left Arrow */
    0,
    KBD_RIGHT_KEY_ID, /* Right Arrow */
    '+',
    0, /* 79 - End key*/
    KBD_DOWN_KEY_ID, /* Down Arrow */
    0, /* Page Down */
    0, /* Insert Key */
    KBD_DELETE_KEY_ID, /* Delete Key */
    0, 0, 0,
    0, /* F11 Key */
    0, /* F12 Key */
    0, /* All other keys are undefined */
};
