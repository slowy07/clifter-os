#include <gui/vga/widget.h>
#include <drv/video/video.h>
#include <string/string.h>

void fillrect_widget_inst(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t colorHex) {
    if (strcmp(video_driver_mode, "GRAPHICS") != 0)
        return;

    for (uint32_t Y = y; Y < y+h; Y++)
        for (uint32_t X = x; X < x+w; X++)
            video_drivers[VGA_VIDEO_DRIVER_INDEX] -> put_pixel(X, Y, colorHex);
}

widget_vga_t* createWidget(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t color) {
    widget_vga_t* widget = 0;

    widget->x  = x;
    widget->y  = y;
    widget->w  = w;
    widget->h  = h;
    widget->color = color;

    fillrect_widget_inst(x, y, w, h, color);

    return widget;
}
