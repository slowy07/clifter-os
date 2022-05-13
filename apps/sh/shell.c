#include <sh/values.h>
#include <clear/clear.h>
#include <boneos_logo/boneos_logo.h>
#include <stdio/stdio.h>
#include <strcmp/strcmp.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <sh/shell.h>
#include <stdbool.h>
#include <help/help.h>
#include <sleep/sleep.h>
#include <echo/echo.h>
#include <string/string.h>
#include <cursor/cursor.h>
#include <reboot/sbin_cmd_reboot.h>
#include <poweroff/sbin_cmd_poweroff.h>
#include <boneshell/boneshell.h>
#include <assertk.h>
#include <drv/driver.h>
#include <sh/built-in/exit/exit.h>

volatile bool TERMINAL_MODE = false;
volatile uint32_t cmd_active_index = 0;

volatile uint32_t shell_instance_cnt = 0;

volatile struct type_cmd cmd_active;

struct cmd_t *cmds[] = {
    &cmd_clear,
    &cmd_clifteros_logo,
    &cmd_help,
    &cmd_sleep,
    &cmd_echo,
    &cmd_cursor,
    &cmd_reboot,
    &cmd_poweroff,
    &cmd_cliftershell,
    &cmd_exit
    ,0
};

void init_terminal() {
    assertkm(device_initalized(KBD_DRIVER_INDEX), "Keyboard not intalized for starting shell!");
    TERMINAL_MODE = true;
    cmds[CMD_CLIFTEROS_LOGO_INDEX] -> handler("clifteros_logo");
    cmds[CMD_CLIFTERSHELL_INDEX] -> handler("cliftershell");
    TERMINAL_MODE = false;
}
