#include <drv/video/video.h>
#include <drv/video/VGA/vga.h>

size_t video_driver_width = 80;
size_t video_driver_height = 25;
char* vide_driver_name = "VGA";
char* video_driver_mode = "TEXTMODE";
char* video_driver_fullname = "VGA_TEXTMODE_80_x_25";

struct video_driver_t *video_drivers[] = {
    &vga_driver,
    0
};
