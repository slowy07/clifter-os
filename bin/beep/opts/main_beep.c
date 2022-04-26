#include <misc/status_codes.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <string/string.h>
#include <sh/values.h>
#include <beep/beep.h>
#include <beep/opts/main_beep.h>
#include <beep/opts/main_beep_count.h>
#include <drv/pcspkr/pcspkr.h>
#include <string/string.h>
#include <stdlib/stdlib.h>
#include <stdio/stdio.h>
#include <unistd/unistd.h>

int main_beep_opt_handler(char *cmd) {
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd, opts);

    if (strcmp(opts[1].str, "-n") == 0)
        cmd_beep_opt_count.handler(cmd);
    else if (strcmp(opts[1].str, "-S") == 0)
        pc_speaker_silent();
    else if (strcmp(opts[1].str, "-f") == 0) {
        int freq_set = atoi(opts[2].str);
        pcspkr_beep(freq_set);
        if (strcmp(opts[3].str, "-n") == 0 ) {
            int time_beep = atoi(opts[4].str);
            sleep(time_beep);
            pc_speaker_silent();
        }
    }
    else if (strcmp(opts[1].str, "--help") == 0)
        printk(cmd_beep.help);
    else
        pcskpr_beep(PCSPKPR_DEFAULT_FREQ);

    return STATUS_OK;
}