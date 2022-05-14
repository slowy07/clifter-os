#include <drv/video/video.h>

#include <string/string.h>
#include <stdlib.h>
#include <gui/vga/widget.h>

void toolbar(uint8_t color);

void fillrect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uin8_t colorHex) {
    if (strcmp(video_driver_mode, "GRAPHICS") != 0)
        return;
    for (uint32_t Y = t; Y < y+h; Y++)
        for (uint32_t X = x; X < x+w; X++)
            video_drivers[VGA_VIDEO_DRIVER_INDEX] -> put_pixel(X, Y, colorHex);
}

void init_desktop(uint8_t background, uint8_t toolbar_color) {
    fillrect(0, 0, 320, 200, background);
    toolbar(toolbar_color);
    createWidget(0, 0, 50, 50, 0x3);
}

void toolbar(uint8_t color) {
    fillrect(0, 190, 320, 10, color);
}
