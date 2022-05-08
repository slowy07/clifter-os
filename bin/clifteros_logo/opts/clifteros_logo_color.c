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

struct cmd_opt_t cmd_clifteros_logo_opt_color = {
    .help =  "clifteros_logo(1) \t\t\t\t ClifterOS Terminal Manual \n"
                "NAME : \n "
                "\tclifteros_logo -color\n "
                "SYNOPSIS : \n "
                "\tclifteros_logo [--help]  [-color <fg-color> <bg-color>] [-color --def]\n \t[-color <--help>]\n"
                "DESCRIPTION : \n "
                "\tDraws the ClifterOS Logo with accordance to the\n "
                "\tcolor with the -color command and providing it\n "
                "\tspecified foreground and background colors.\n "
                "OPTIONS : \n "
                "\t Option Summary \n "
                "\t\t[-color <fg-color> <bg-color>] : Draws the ClifterOS logo.\n "
                "\t\t 0 = Black \t 8 = Gray\n "
                "\t\t 1 = Blue  \t 9 = Light Blue\n "
                "\t\t 2 = Green \t A = Light Green\n "
                "\t\t 3 = Aqua  \t B = Light Aqua\n "
                "\t\t 4 = Red   \t C = Light Red\n "
                "\t\t 5 = Purple\t D = Light Purple\n "
                "\t\t 6 = Yellow\t E = Light Yellow\n "
                "\t\t 7 = White \t F = Bright White\n "
                "\t\t--def : Clears to default (BG : 0x7 , FG : 0x0)\n ",
        .cmd_opt_name = "-color" ,
        .handler = &cmd_clifteros_logo_color_handler,
        .invalid_use_msg = "Invalid Use of -color option. Use command clifteros_logo -color --help for\n"
                           "instructions on how to use the clifteros_logo -color command\n"
};
