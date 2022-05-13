
#include <stdio/stdio.h>
#include <misc/status_codes.h>
#include <unistd/unistd.h>
#include <string/string.h>
#include <sh/shell.h>
#include <sh/built-in/exit/exit.h>

extern volatile bool exit_set__shell;

struct cmd_opt_t* cmd_exit_opts[] = {
    0
};

int exit_handler(char* cmd) {
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd, opts);

    if (num_opts == 1) {
        exit_set__shell = true;
        return STATUS_OK;
    }
    else if (strcmp(opts[1].str, "--help") == 0)
        printl(cmd_exit.help);
    else
        printk(cmd_exit.invalid_use_msg);

    return STATUS_OK;
}

struct cmd_t cmd_exit = {
  .name = "exit",
  .usage = "exit [--help] ",
  .help = "exit(1) \t\t\t\t ClifterOS Terminal Manual \n"
                "NAME : \n "
                "\texit\n"
                "SYNOPSIS : \n "
                "\texit [--help]\n"
                "DESCRIPTION : \n "
                "\tCommand to exit the current \n "
                "\tshell process\n",
  .cmd_opts =  cmd_exit_opts,
  .handler = &exit_handler,
  .invalid_use_msg = "Invalid use of exit command.\n"
                     "Type in exit --help for more help.\n",
  .privilege = USER
};