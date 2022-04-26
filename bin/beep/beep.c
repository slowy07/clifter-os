#include <misc/status_codes.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <string/string.h>
#include <sh/values.h>
#include <beep/beep.h>
#include <beep/opts/main_beep.h>

struct cmd_opt_t* cmd_beep_opts
{
    /* data */
    0
};

int cmd_beep_handler (char *cmd) {
    return main_beep_opt_handler (cmd);
}

struct cmd_t cmd_beep = {
  .name = "beep",
  .usage ="beep [-n milliseconds] [-f freq] [--help]",
  .help = "beep(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n "
                "\tbeep\n"
                "SYNOPSIS : \n "
                "\tbeep [-n milliseconds] [-f freq] [-S] [--help]\n"
                "DESCRIPTION : \n "
                "\tBeeps via the PC Speaker. if used without\n"
                "\t-n option, defaults to beep forever. If freq not\n"
                "\tset with -f then default if of 1000 htz.\n",
  .cmd_opts =  cmd_beep_opts,
  .handler = &cmd_beep_handler,
  .invalid_use_msg = "Invalid use of beep command.\n"
                     "Type in beep --help for more help.\n",
  .privilege = USER
};
