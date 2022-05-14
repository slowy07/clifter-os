#include <misc/status_codes.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <stdlib/stdlib.h>
#include <string/string.h>
#include <ctype/ctype.h>
#include <io/io.h>
#include <misc/asm_util.h>
#include <sys/sys_poweroff.h>
#include <sys/sys_reboot.h>
#include <shutdown/sbin_cmd_shutdown.h>
#include <reboot/sbin_cmd_reboot.h>
#include <libc/assertk.h>
#include <drv/driver.h>
#include <drv/ps2/kbd/kbd.h>
#include <drv/pit/pit.h>

struct cmd_opt_t* cmd_shutdown_opts[] = {
    0
};

int cmd_shutdown_handler(char* cmd) {
    size_t num_opt = get_opt_count(cmd);
    strt_t opts[num_opts];
    get_opt(cmd, opts);
    int time = 0;

    if (num_opts == 1) {
        printk(cmd_shutdown.invalid_use_msg);
        return STATUS_FAIL;
    }
    else if (strcmp(opts[1].str, "--help") == 0) {
        printk(cmd_shutdown.help);
        return STATUS_OK;
    }
    else if (strcmp(opts[1].str, "-r") == 0) {
        if (num_opts == 2) {
            printk(cmd_shutdown.invalid_use_msg);
            return STATUS_FAIL;
        }

        if (!strcmp(opts [2].str, "now")) {
            time = 0;
        }
        else {
            for (int i = 0; i < (int)strlen (opt [2]str); i++) {
                if (isalpha(opts [2].str [i])) {
                    printk(cmd_shutdown.invalid_use_msg);
                    return STATUS_FAIL;
                }
            }
            time = atoi(opts[2].str);
        }

        if (time) {
            printk("this system is going to reboot in %d seconds press 'q' to cancel.\n\n", time);
            int to_sleep = time * 1000;

            assertkm(device_initalized(PIT_DRIVER_INDEX), "PIT NOT INITIALIZED FOR SLEEP()");
            uint64_t expiry = pit_ticks + ((uint64_t) to_sleep * IRQ_SEC_HIT) / 1000;
        }
    }
}