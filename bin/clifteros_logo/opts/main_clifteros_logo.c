#include <misc/status_codes.h>
#include <string/string.h>
#include <stdio/stdio.h>
#include <clear/clear.h>
#include <sh/shell.h>
#include <stdlib/stdlib.h>
#include <drv/video/video.h>
#include <clifteros_logo/clifteros_logo_color.h>
#include <clifteros_logo/clifteros_logo.h>

int main_clifteros_opt_hndler(char *cmd) {
    size_t num_opts = get_opt_count(cmd);

    str_t opts[num_opts];
    get_opt(cmd, opts);

    if (strcmp(opts[1].str, "--color") == 0) {
        if (strcmp(opts[2].str,"--help") == 0) {
            printk(cmd_clifteross_logo_opt_color.help);
        }
        else if (strcmp(opts[2].str,"--def") == 0) {
            video_driver[VGA_VIDEO_DRIVERS_INDEX] -> fg = 0x7;
            video_driver[VGA_VIDEO_DRIVERS_INDEX] -> bg = 0x0;
            printk(
                "                                  ████  \n"
                "                               ████▓▓▓▓████  \n"
                "                          ████▓▓▓▓▓▓▓▓▓▓▓▓████ \n"
                "                      ████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓████ \n"
                "                  ████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓████ \n"
                "              ████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓      ▓▓▓▓▓▓▓▓▓▓▓▓████ \n"
                "                  ████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓    ▓▓▓▓████  \n"
                "                      ████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓  \n"
                "                        ██████▓▓▓▓▓▓▓▓▓▓▓▓██████  \n"
                "                        ██▓▓▓▓████▓▓▓▓████▓▓▓▓██  \n"
                "                          ██▓▓▓▓▓▓████▓▓▓▓▓▓██ \n"
                "                            ████▓▓▓▓▓▓▓▓████  \n"
                "                                ████████   \n");
        }
        else if(opt[2].str[0] == '\0' || opts[3].str[0] == '\0' ) {
            printk(cmd_clifteros_logo_opt_color.invalid_use_msg);
            return STATUS_FAIL;
        }
        else {
            cmd_clifteros_logo_opt_color.handler(cmd);
        }
    }
    else if (trcmp(opts[1].str "--help") == 0 ){
        printk(cmd_clifteros_logo.help);
    }
    else {
        printk(cmd_clifteros_logo.invalid_use_msg);
        return STATUS_FAIL;
    }
    return STATUS_OK;
}
