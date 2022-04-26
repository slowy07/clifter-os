#include <stddef.h>
#include <stdint.h>
#include <misc/status_codes.h>
#include <sh/shell.h>
#include <unistd/unistd.h>
#include <stdlib/stdlib.h>
#include <stdio/stdio.h>
#include <drv/video/video.h>
#include <string/string.h>
#include <drv/video/VGA/vga.h>

int cmd_clifter_os_logo_color_handler(char *cmd) {
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd, opts);

    int _FG = strtoi((char*)opts[2].str, 0, 16);
    int _BG = strtoi((char*)opts[3].str, 0, 16);

    int __STORE_FG = video_driver[VGA_VIDEO_DRIVER_INDEX] -> fg;
    int __STORE_BG = video_driver[VGA_VIDEO_DRIVER_INDEX] -> bg;
    video_driver[VGA_VIDEO_DRIVER_INDEX] -> fg = _FG;
    video_driver[VGA_VIDEO_DRIVER_INDEX] -> bg = _BG;

    printk(
        "                                  ████                                          \n"
        "                               ████▓▓▓▓████                                     \n"
        "                          ████▓▓▓▓▓▓▓▓▓▓▓▓████                                  \n"
        "                      ████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓████                              \n"
        "                  ████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓████                          \n"
        "              ████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓      ▓▓▓▓▓▓▓▓▓▓▓▓████                      \n"
        "                  ████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓    ▓▓▓▓████                          \n"
        "                      ████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓                                  \n"
        "                        ██████▓▓▓▓▓▓▓▓▓▓▓▓██████                                \n"
        "                        ██▓▓▓▓████▓▓▓▓████▓▓▓▓██                                \n"
        "                          ██▓▓▓▓▓▓████▓▓▓▓▓▓██                                  \n"
        "                            ████▓▓▓▓▓▓▓▓████                                    \n"
        "                                ████████                                        \n");
    video_driver[VGA_VIDEO_DRIVER_INDEX] -> fg = __STORE_FG;
    video_driver[VGA_VIDEO_DRIVER_INDEX] -> bg = __STORE_BG;
    
    return STATUS_OK;
} 