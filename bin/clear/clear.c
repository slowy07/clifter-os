#include <misc/status_codes.h>
#include <sh/shell.h>
#include <clear/opts/color.h>
#include <drv/video/VGA/vga.h>
#include <stdio/stdio.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <clear/opts/main_clear.h>


struct cmd_opt_t* cmd_clear_opts[] = {
    &cmd_clear_opt_color,
    0
};

int cmd_clear_handler(char* cmd) {
    size_t num_opts = get_opt_count(cmd);
    if (num_opts == 1) {
        video_drivers[VGA_VIDEO_DRIVER_INDEX] -> clear();
        return STATUS_OK;
    }
    
    main_clear_opt_handler(cmd);
    
    return STATUS_OK;
}


struct cmd_t cmd_clear = {
  .name = "clear",
  .usage = "clear [--help]  [-color <fg-color> <bg-color>] [-color --def]  [-color <--help>] ",
  .help = "clear(1) \t\t\t\t ClifterOS Terminal Manual \n"
                "NAME : \n "
                "\tclear\n"
                "SYNOPSIS : \n "
                "\tclear [--help]  [-color <fg-color> <bg-color>] [-color --def] [-color <--help>]\n"
                "DESCRIPTION : \n "
                "\tClears the terminal. Possible to specifiy the\n "
                "\tcolor with the -color command and providing it\n "
                "\ta Foreground as well as a Background Color \n"
                "MORE HELP : \n "
                "\t[clear -color --help] for help on -color option\n",   
  .cmd_opts =  cmd_clear_opts,
  .handler = &cmd_clear_handler,    
  .invalid_use_msg = "Invalid use of clear command.\n"
                     "Type in clear --help for more help.\n",
  .privilege = USER
};
