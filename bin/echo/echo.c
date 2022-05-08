#include <misc/status_codes.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <echo/echo.h>
#include <echo/opts/main_echo.h>

struct cmd_opt_t* cmd_echo_opts[] = {
    0
};

int cmd_echo_handler(char* cmd) {
    size_t num_opts = get_opt_count(cmd);
    if (num_opts == 1) {
        printk(cmd_echo.invalid_use_msg);
        
        return STATUS_OK;
    }
}

struct cmd_t cmd_echo = {
  .name = "echo",
  .usage ="echo [value]",
  .help = "echo(1) \t\t\t\t ClifterOS Terminal Manual \n"
                "NAME : \n "
                "\techo\n"
                "SYNOPSIS : \n "
                "\techo [value]\n"
                "DESCRIPTION : \n "
                "\tPrints out the VALUE listed by option\n",
  .cmd_opts =  cmd_echo_opts,
  .handler = &cmd_echo_handler,    
  .invalid_use_msg = "Invalid use of echo command.\n"
                     "Type in echo --help for more help.\n",
  .privilege = USER
};
