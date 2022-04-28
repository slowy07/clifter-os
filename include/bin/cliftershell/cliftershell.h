#ifndef _BIN_CLIFTER_SHELL_H_
#define _BIN_CLIFTER_SHELL_H_

#include <unistd/unistd.h>

extern volatile bool new_set__shell;
extern struct cnd_t cmd_cliftershell;
extern volatile bool exit_set__shell;
extern volatile bool skip_prints;
extern int total_cmd;

#endif // _BIN_CLIFTER_SHELL_H_
