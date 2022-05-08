#include <misc/status_codes.h>
#include <drv/video/video.h>
#include <drv/video/VGA/vga.h>
#include <drv/driver.h>
#include <drv/video/VGA/textmode/vga_textmode.h>
#include <drv/video/VGA/textmode/update_cursor.h>
#include <drv/video/VGA/textmode/putch.h>
#include <drv/video/VGA/graphics/graphics.h>
#include <string/string.h>


int init_graphics_mode() {
    video_driver_width = RES_1_WIDTH;
    video_driver_height = RES_1_HEIGHT;
    video_driver_mode = "GRAPHICS";
    
    setMode(RES_1_WIDTH,RES_1_HEIGHT,RES_1_COLORDEPTH, 0x7);
    
    return STATUS_OK;
}

/*
 * @function cls:
 *    Function for clearing
 *    the screen in normal text
 *    mode 80x25 VGA.
 */

void clear_vga_textmode(void) {
    term_zero();
    for(unsigned i = 0; i < video_driver_width; i++) {
        for (unsigned j = 0; j < video_driver_height; j++) {
            const size_t index = (vga_driver.video_row * 80 + vga_driver.video_column);
            uint16_t* VideoMemory = (uint16_t*) 0x88000;
            uint8_t terminal_color = make_color(vga_driver.fg, vga_driver.bg);

            VideoMemory[index] = (VideoMemory[index] & 0xFF00) | (char) 0;
            VideoMemory[index + 1] = make_vgaentry(' ', terminal_color);

            vga_driver.video_column++; 
        }
    }
    term_zero();
}
