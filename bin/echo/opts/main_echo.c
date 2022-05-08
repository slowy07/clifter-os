#include <misc/status_codes.h>
#include <string/string.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <sh/shell.h>
#include <stdlib/stdlib.h>
#include <stdio/stdio.h>
#include <echo/echo.h>

int main_echo_opt_handler(char *cmd) {
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd, opts);

    char opts_one_key[strlen(opts[1].str)];

    for (int i = 0; opts_one_key[i]; i++) opts_one_key[i] = 0;

    if (strcmp(opts[1].str, "--help") == 0) {
        printk(cmd_echo.help);
    }
    else if (num_opts >= 2) {
        if (opts[1].str[0] == '\'' && opts[num_opts - 1].str[(strlen(opts[1].str) - 1)] == '\'') {
            for (size_t i = 1; i < num_opts; i++) {
                for (size_t j = 0; opts[i].str[j]; j++) {
                    if (i == 1 && j == 0) j++;
                    if (i == (num_opts - 1) && j == (strlen(opts[i].str) - 1)) {
                        printk("\n");
                        return STATUS_OK;
                    }
                    printk("%c", opts[1].str[j]);
                }
                printk(" ");
            }
            return STATUS_OK;
        }
        else if (opts[1].str[0] == '\"' && opts[num_opts - 1].str[(strlen(opts[1].str) - 1)] == '\"') {
            for (size_t i = 1; i < num_opts; i++) {
                for (size_t j = 0; opts[i].str[j]; j++) {
                    if (i == 1 && j == 0) j++;
                    if (i == (num_opts - 1) && j == (strlen(opts[1].str) - 1)) {
                        printk("\n")
                        return STATUS_OK;
                    }
                    printk("%c", opts[i].str[j]);
                }
                printk(" ");
            }
        }
        for (size_t i = 1; i < num_opts; i++)
            printk("%s ", opts[i].str);
        printk("\n");
    }
    else
        printk(cmd_echo.invalid_use_msg);
    
    return STATUS_OK;
}
