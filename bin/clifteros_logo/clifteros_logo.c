#include <stdio/stdio.h>
#include <misc/status_codes.h>
#include <sh/shell.h>
#include <unistd/unistd.h>
#include <drv/video/VGA/vga.h>
#include <clifteros_logo/opts/clifteros_logo_color.h>
#include <clifteros_logo/opts/main_clifteros_logo.h>

struct cmd_opt_t* cmd_clifteros_logo_opt[] = {
    /* data */
    &cmd_clifteros_logo_opt_color,
    0
};

int clifteros_logo_handler(char* cmd) {
    size_t num_opts = get_opt_count(cmd);
    if (num_opts == 1) {
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
        return STATUS_OK;
    }
    return main_clifteros_opt_handler(cmd);
}

struct cmd_t cmd_clifteros_logo = {
    .name = "clifteros_logo",
    .usage = "clifteros_logo [--help]  [-color <fg-color> <bg-color>] [-color --def] [-color <--help>] ",
    .help = "clifteros_logo(1) \t\t\t\t ClifterOS Terminal Manual \n"
                    "NAME : \n "
                    "\tclifteros_logo\n"
                    "SYNOPSIS : \n "
                    "\tclifteros_logo [--help]  [-color <fg-color> <bg-color>] [-color --def] [-color <--help>]\n"
                    "DESCRIPTION : \n "
                    "\tCommand that draws the BoneOS logo\n "
                    "\tonto terminal. use the -color command\n "
                    "\tto have a specific Foreground and Background Color\n"
                    "MORE HELP : \n "
                    "\t[clifteros_logo -color --help] for help on -color option\n",
    .cmd_opts =  cmd_clifteros_logo_opts,
    .handler = &clifteros_logo_handler,
    .invalid_use_msg = "Invalid use of clifteros_logo command.\n"
                        "Type in clifteros_logo --help for more help.\n",
    .privilege = USER
};

