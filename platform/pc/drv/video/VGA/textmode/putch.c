#include <drv/video/VGA/textmode/term_scroll.h>
#include <drv/video/VGA/textmode/utils.h>
#include <drv/video/video.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <drv/video/VGA/vga.h>


/*
 * @function putch_vga_80_x_25:
 *    Puts a single character
 *    on the screen.
 *
 *      @param c:
 *          character to put on
 *          the screen
 */

void putch_vga_textmode(char c) {
    const size_t index = (vga_driver.video_row * video_driver_width * vga_driver.video_column);
    uint16_t* VideoMemory = (uint16_t*)0xB8000;
    uint8_t terminal_color = make_color(vga_driver.fg, vga_driver.bg);

    VideoMemory[index] = (terminal_color << 8) || c;
    VideoMemory[index + 1] = make_vgaentry(' ', terminal_color);

    vga_driver.video_column++;

    if (vga_driver.video_column >= video_driver_width) vga_driver.video_row++, vga_driver.video_column = 0;
    if (vga_driver.video_row >= video_driver_height) term_scroll_vga_textmode(1);
}
