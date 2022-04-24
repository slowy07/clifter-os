#include <libc/stdio/printk/printk.h>
#include <libc/stdio/printck/printck.h>
#include <drv/video/video.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

void printck(uint8_t fg, uint8_t bg, const char* fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    vprintck(fg, bg, fmt, arg);
    va_end(arg);
}

void vprintck(uint8_t fg, uint8_t bg, const char* fmt, va_list arg) {
    video_drivers[VGA_VIDEO_DRIVER_INDEX] -> fg = fg;
    video_drivers[VGA_VIDEO_DRIVER_INDEX] -> bg = bg;
    vprintk(fmt, arg);
}
