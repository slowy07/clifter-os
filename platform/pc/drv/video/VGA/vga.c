#include <misc/status_codes.h>
#include <drv/video/video.h>
#include <drv/video/VGA/vga.h>
#include <drv/driver.h>
#include <drv/video/VGA/textmode/vga_textmode.h>
#include <drv/video/VGA/textmode/update_cursor.h>
#include <drv/video/VGA/textmode/putch.h>
#include <drv/video/VGA/graphics/graphics.h>
#include <drv/video/VGA/graphics/vga_graphics.h>
#include <string/string.h>


struct video_driver_t vga_driver = {
    .init = &init_vga_driver,
    .uninit = &uninit_vga_driver,
    .statu = STATUS_DRIVER_OK
};

void set_mode_util(putch_t putch_v, put_pixel_t put_pixel_v, clear_t clear_v, update_cursor_t update_cursor_v, scroll_t scroll_v) {
    vga_driver.putch = putch_v;
    vga_driver.put_pixel = put_pixel_v;
    vga_driver.clear = clear_v; 
    vga_driver.update_cursor = update_cursor_v; 
    vga_driver.scroll = scroll_v;
}

int uninit_vga_driver() {
    video_driver.initialized = false;
    set_mode_util(0, 0, 0, 0, 0);

    return STATUS_OK;
}

int init_vga_driver() {
    video_driver.initalized = true;
    vga_driver.res.w = video_driver_width;
    vga_driver.res.h = video_driver_height;

    if (strcmp(video_driver_mode, "TEXTMODE") == 0) {
        vga_driver.mode = TEXT_MODE;
        vga_driver.put_pixel = 0;
        init_vga_textmode();
        set_mode_util(
            vga_textmodes_arr[0] -> putch,
            0,
            vga_textmodes_arr[0] -> clear,
            vga_textmodes_arr[0] -> update_cursor,
            vga_textmodes_arr[0] -> scroll
        );

        vga_driver.name = vga_textmodes_arr[0] -> name;
        vga_driver.fg = 7;
        vga_driver.bg = 0;
    }
    else if (strcmp(video_driver_mode, "GRAPHICS") == 0) {
        vga_driver.mode = GRAPHICS_MODE;
        vga_driver.put_pixel = vgaGraphicsPutPixel;
        init_graphics_mode();
        set_mode_util(
            0,
            vgaGraphicsPutPixel,
            clearVgaGraphics,
            0,
            0
        );
        vga_driver.name = "VGA_TEXTMODE_320_x_200";
        vga_driver.fg = 7;
        vga_driver.bg = 0;  
    }
    return STATUS_OK;
}
