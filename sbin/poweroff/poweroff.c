#include <misc/status_codes.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <string/string.h>
#include <io/io.h>
#include <misc/asm_util.h>
#include <sys/sys_poweroff.h>
#include <poweroff/sbin_cmd_poweroff.h>
#include <reboot/sbin_cmd_reboot.h>
#include <sys/sys_poweroff.h>


struct cmd_opt_t* cmd_poweroff_opts[] = {
    0
};

int cmd_poweroff_handler(char* cmd) {
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd, opts);

    if (num_opts == 1)
        root_sys_poweroff();
    else if (strcmp(opts[1].str, "--help") == 0)
        printk(cmd_poweroff.help);
    else {
        printk(cmd_poweroff.invalid_use_msg);
        return STATUS_FAIL;
    }

    return STATUS_OK;
}

struct cmd_t cmd_poweroff = {
    name = "poweroff",
    .usage ="poweroff [--help]",
    .help = "poweroff(1) \t\t\t\t ClifterOS Terminal Manual \n"
            "NAME : \n "
            "\tpoweroff\n"
            "SYNOPSIS : \n "
            "\tpoweroff [--help]\n"
            "DESCRIPTION : \n "
            "\tShuts down the Operating System. Currently only working in Bochs and Qemu.\n",
    .cmd_opts = cmd_poweroff_opts,
    .handler = &cmd_poweroff_handler,
    .invalid_use_msg = "Invalid use of poweroff command.\n"
            "Type in poweroff --help for more help.\n",
    .privilege = ROOT
};
