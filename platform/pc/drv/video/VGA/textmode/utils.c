#include <stddef.h>
#include <stdint.h>

/*
 * @inline make_color:
 *      converts FG And BG
 *      to a 8bit integer
 *      color.
 */

uint8_t make_color(uint8_t fg, uint8_t bg) {
    return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color) {
    return ((uint16_t) c | (uint16_t) color << 8);
}
