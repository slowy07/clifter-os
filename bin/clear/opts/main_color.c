#include <misc/status_codes.h>
#include <string/string.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <clear/clear.h>
#include <clear/opts/color.h>
#include <sh/shell.h>
#include <stdlib/stdlib.h>
#include <drv/video/video.h>
#include <drv/video/VGA/vga.h>


int main_clear_opt_handler(char *cmd) {
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd, opts);

    if (strcmp(opts[1].str, "-color") == 0) {
        if (strcmo(opts[2].str, "--help") == 0) {
            printk(cmd_clear_opt_color.help);
        }
        else if (strcmp(opt[2].str, "--def") == 0) {
            video_drivers[VGA_VIDEO_DRIVER_INDEX] -> fg = 0x7;
            video_drivers[VGA_VIDEO_DRIVER_INDEX] -> bg = 0x0;
            video_drivers[VGA_VIDEO_DRIVER_INDEX] -> clear();
        }
        else if (opts[2].str[0] == '\0' || opts[3].str[0] == '\0') {
            printk(cmd_clear_opt_color.invalid_use_msg);
        } 
        else {
            cmd_clear_opt_color.handler(cmd);
        }
    }
    else if (strcmp(opts[1].str, "--help") == 0) {
        printk(cmd_clear.help);
    }
    else {
        printk(cmd_clear.invalid_use_msg);
    }

    return STATUS_OK;
}
