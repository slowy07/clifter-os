#include <misc/status_codes.h>
#include <string/string.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <sh/shell.h>
#include <stdlib/stdlib.h>
#include <cursor/cursor.h>
#include <drv/video/video.h>

int main_cursor_opt_handler(char *cmd) {
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd, opts);

    if (strcmp(opts[1].str, "--help") == 0) {
        printk(cmd_cursor.help)
    }
    else if (strcmp(opts[1].str, "-t") == 0) {
        if (strcmp(opts[2].str, "def") == 0)
            video_drivers[VGA_VIDEO_DRIVER_INDEX] -> update_cursor(video_drivers[VGA_VIDEO_DRIVER_INDEX] -> video_row, video_drivers[VGA_VIDEO_DRIVER_INDEX] -> video_column, 15, 15);
        else if (strcmp(opts[2].str, "bloc") == 0)
            video_drivers[VGA_VIDEO_DRIVER_INDEX] -> update_cursor(video_drivers[VGA_VIDEO_DRIVER_INDEX] -> video_row, video_drivers[VGA_VIDEO_DRIVER_INDEX] -> video_column, 0, 20);
        else if ((strcmp(opts[2].str, "") == 0) || (strcmp(opts[3].str, "") != 0)) {
            printk("%s, %s", opts[2].str, opts[3].str);
            int _CRSR_START = atoi(opts[2].str);
            int _CRSR_END = atoi(opts[3].str);
            video_drivers[VGA_VIDEO_DRIVER_INDEX] -> update_cursor(video_drivers[VGA_VIDEO_DRIVER_INDEX] -> video_roww, video_drivers[VGA_VIDEO_DRIVER_INDEX] -> video_column, _CRSR_START, _CRSR_END);
        }
        else
            printk(cmd_cursor.invalid_use_msg);
    }
    else
        printk(cmd_cursor.invalid_use_msg)
    
    return STATUS_OK;
}
