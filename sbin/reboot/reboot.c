#include <misc/status_codes.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <string/string.h>
#include <io/io.h>
#include <misc/asm_util.h>
#include <sys/sys_reboot.h>
#include <reboot/sbin_cmd_reboot.h>

struct cmd_opt_t* cmd_reboot_opts[] = {
    0
};

int cmd_reboot_handler(char* cmd) {
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd, opts);

    if (num_opts == 1)
        root_sys_reboot();
    else if (strcmp(opts[1].str, "--help") == 0)
        printk(cmd_reboot.help);
    else {
        printk(cmd_reboot.invalid_use_msg);
        return STATUS_FAIL;
    }

    return STATUS_OK;
}

struct cmd_t cmd_reboot =
{
    .name = "reboot",
    .usage ="reboot [--help]",
    .help = "reboot(1) \t\t\t\t ClifterOS Terminal Manual \n"
            "NAME : \n "
            "\treboot\n"
            "SYNOPSIS : \n "
            "\treboot [--help]\n "
            "DESCRIPTION : \n "
            "\tReboots the Operating System.\n",
    .cmd_opts = cmd_reboot_opts,
    .handler = &cmd_reboot_handler,
    .invalid_use_msg = "Invalid use of reboot command.\n"
            "Type in reboot --help for more help.\n",
    .privilege = ROOT
};
