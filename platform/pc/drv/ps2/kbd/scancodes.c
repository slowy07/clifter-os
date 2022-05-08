#include <drv/ps2/kbd/scancodes.h>
#include <drv/ps2/kbd/kbd.h>

struct kbd_layout_t QWERTY_USA = {
    .scancode_shift = QWERTY_USA_SHIFT_VAL,
    .scancode_no_shift = QWERTY_USA_NOSHIFT_VAL,
    .name = "QWERTY_USA",
    .country = "USA"
};

struct kbd_layout_t *kbd_layout[] = {
    /* data */
    &QWERTY_USA,
    0
};
