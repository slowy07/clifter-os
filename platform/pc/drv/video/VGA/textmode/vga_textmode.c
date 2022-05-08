#include <io/io.h>
#include <misc/status_codes.h>
#include <drv/video/VGA/textmode/clear.h>
#include <drv/video/VGA/textmode/putch.h>
#include <drv/video/VGA/textmode/vga_textmode.h>
#include <drv/video/VGA/textmode/update_cursor.h>
#include <drv/video/VGA/textmode/term_scroll.h>
#include <drv/video/VGA/textmode/cursor.h>
#include <drv/video/video.h>
#include <stddef.h>
#include <stdint.h>

int init_vga_textmode() {
    __textmode.w = video_driver_width;
    __textmode.h = video_driver_height;
    __textmode.name = video_driver_fullname;
    return STATUS_OK;
}

vga_textmode_t __textmode = {
    .clear = &clear_vga_textmode,
    .putch = &putch_vga_textmode,
    .update_cursor = &update_cursor_textmode,
    .scroll = &term_scroll_textmode,
    .init = &init_vga_textmode
};

vga_textmode_t *vga_textmode_arr[] = {
    &__textmode,
    0
};
