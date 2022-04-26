#include <stddef.h>
#include <stdint.h>
#include <misc/status_codes.h>
#include <sh/shell.h>
#include <unistd/unistd.h>
#include <stdlib/stdlib.h>
#include <stdio/stdio.h>
#include <string/string.h>
#include <beep/opts/main_beep.h>
#include <beep/opts/main_beep_count.h>
#include <drv/pcspkr/pcspkr.h>

int cmd_beep_count_handler(char *cmd) {
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd, opts);

    int __beep_milliseconds = atoi(opts[2].str);

    if (strcmp(opts[2].str, "--help") == 0)
        printk(cmd_beep_opt_count.help);
    else {
        int freq_n_go = PCSPKR_DEFAULT_FREQ;
        if (strcmp(opts[3].str, "-f") == 0)
            freq_n_go = atoi(optsp[4].str);

        pcspkr_beep(freq_n_go);
        sleep(__beep_milliseconds);
        pc_speaker_silent();
    }
    return STATUS_OK;
}

struct cmd_opt_t cmd_beep_opt_count = {
    .help =  "beep(1) \t\t\t\t Clifter Os Terminal Manual \n"
                "NAME : \n "
                "\tbeep -n\n "
                "SYNOPSIS : \n "
                "\tbeep [-n milliseconds] [-f freq] [--help]\n"
                "DESCRIPTION : \n "
                "\tBeeps with a frequency of freq or default 1000\n "
                "\tfor n milliseconds.\n",
        .cmd_opt_name = "-n" ,
        .handler = &cmd_beep_count_handler,
        .invalid_use_msg = "Invalid Use of -n option. Use command beep -n --help for\n"
                           "instructions on how to use the beep -n command\n"
};