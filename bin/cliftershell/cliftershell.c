#include <stdio/stdio.h>
#include <misc/status_codes.h>
#include <unistd/unistd.h>
#include <cliftershell/cliftershell.h>
#include <string/string.h>
#include <sh/shell.h>
#include <sh/values.h>
#include <sh/utils.h>
#include <drv/video/VGA/vga.h>
#include <libc/stdio/scank/scank.h>
#include <drv/ps2/kbd/kbd.h>
#include <drv/cmos/rtc/rtc.h>
#include <../platform/pc/drv/ps2/kbd/kbd.c>
#include <var/cpu/cpu_info.h>

extern volatile bool TAB_PREVIOUS_VALUE_SET;
extern volatile char* TAB_PREVIOUS_VALUE;
extern void key_handler_util(int key);

struct cmd_opt_t* cmd_cliftershell_opts[] = {
    0
};

int __found = 0;
volatile bool exit_set__shell = false;
volatile bool new_set__shell = false;
volatile bool tab_multiple_opts = false;
volatile bool tab_one_opt = false;
volatile bool tab_zero_opt = false;
volatile bool skip_prints = false;
bool executed_internally=false;
int total_cmd = 0;

void removeSpaces(char* source) {
    char* i = source;
    char* j = source;
    while(*j != 0) {
        *i = *j++;
        if (*i != ' ')
            i++;
    }
    *i = 0;
}

void loop_terminal() {
    shell_instance_cnt += 1;
    if (skip_prints == false) {
        if (shell_instance_cnt != 1)
            printk("Shell #%d\n", shell_instance_cnt);

        printk("%s release %s started at ", VAR_OSNAME, VAR_RELEASE);
        start_time = rtc_get_time();
        rtc_print_struct(start_time);
    } 
    for (total_cmd = 0; cmds [total_cmd]; total_cmd ++);

    while(1) {
        start_shell:;
        if (exit_set__shell == true) {
            exit_set__shell = false;
            goto end_shell;
        }

        int FG__ = video_drivers[VGA_VIDEO_DRIVER_INDEX] -> fg;
        int BG__ = video_drivers[VGA_VIDEO_DRIVER_INDEX] -> bg;

        if (video_drivers[VGA_VIDEO_DRIVER_INDEX] -> fg == 0x7 && video_drivers[VGA_VIDEO_DRIVER_INDEX] -> bg == 0x0) {
            printck(2, 0, "%s@clifteros:", VAR_USER);
            printck(1, 0, "%s", VAR_PWD);
            printck(0x0, 0x7,"");
            printck(0x7, 0x0, " $ ");
        }
        else {
            printk("%s@clifteros:", VAR_USER);
            printk("%s", VAR_PWD);  
            printk(" $ ");
        }
        video_drivers[VGA_VIDEO_DRIVER_INDEX] -> fg = FG__;
        video_drivers[VGA_VIDEO_DRIVER_INDEX] -> bg = BG__;

        virtual_cursor_pos = 0;
        virual_index_scank = 0;

        scank(true, true, "%s", cmd_active.value);

        if (tab_multiple_opts == true) {
            tab_multiple_opts = false;
            goto start_shell;
        }
        else if (tab_one_opt == true) {
            tab_one_opt == false;
            strcpy (cmd_active.value, tab__);
            executed_internally = true;
            removeSpaces (cmd_active.value);
        }
        else if (tab_zero_opt == true) {
            key_handler_util_backspace();
            tab_zero_opt = false;
            scank(true, true, "%s", cmd_active.value + (strlen(cmd_active.value)));
        }

        if (strcmp(cmd_active.value, "exit") == 0 || exit_set__shell == true) {
            shell_instance_cnt--;
            exit_set__shell = false;
            strcpy (cmd_active.value, " ");
            printk("Exited shell instance #%d\n", shell_instance_cnt + 1);
            goto end_shell;
        }

        if (new_set__shell == true) {
            new_set__shell = false;
            loop_terminal();
            goto start_shell;
        }

        for (int i = 0; cmds[i]; i++) {
            if (termcmp(cmds[i] -> name, cmd_active.value) == 0) {
                if (executed_internally == true) {
                    executed_internally = false;
                }
                cmds[i] -> handler(cmd_active.value);
                __found = 1;
            }
        }
        if (__found == 0 && cmd_active.valaue [0] != '\0') {
            printk("Invalid Command '%s' \n", cmd_active.value);
            printl("Try 'help' for more information.\n");
        }
        __found = 0;
        cmd_active_index++;
    }
    end_shell:;
}

int cliftershell_handler(char* cmd) {
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd, opts);

    if(strcmp(opts[1].str, "--help") == 0)
        printk(cmd_cliftershell.help);
    else if (num_opts == 1)
        loop_terminal();
    else {
        printk(cmd_cliftershell.invalid_use_msg);
        return STATUS_FAIL;
    }
    return STATUS_OK;
}

struct cmd_t cmd_boneshell =
{
    .name = "cliftershell",
    .usage = "cliftershell [--help] ",
    .help = "cliftershell(1) \t\t\t\t ClifterOS Terminal Manual \n"
                "NAME : \n "
                "\tclifershell\n"
                "SYNOPSIS : \n "
                "\tcliftershell [--help]\n"
                "DESCRIPTION : \n "
                "\tCreates another instance of a shell being \n "
                "\tthe child of the previous parent shell process.\n "
                "\tcommand exit used to stop this child shell process.\n "
                "\ttype exit --help for more on exit command\n ",
    .cmd_opts =  cmd_boneshell_opts,
    .handler = &boneshell_handler,
    .invalid_use_msg = "Invalid use of cliftersshell command.\n"
                        "Type in cliftershell --help for more help.\n",
    .privilege = USER
};
