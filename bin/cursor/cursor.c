
#include <misc/status_codes.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <cursor/cursor.h>
#include <cursor/opts/main_cursor.h>

struct cmd_opt_t* cmd_cursor_opts[] = {
    0
};

int cmd_cursor_handler(char* cmd) {
    size_t num_opts = get_opt_count(cmd);
    if (num_opts == 1) {
        printk(cmd_cursor.invalid_use_msg);
        return STATUS_OK;
    }

    main_cursor_opt_handler(cmd);
    
    return STATUS_OK;
}

struct cmd_t cmd_cursor = {
    .name = "cursor",
    .usage ="cursor [-t <CRSR_START> <CRSR_END>] [-t block] [-t def]",
    .help = "cursor(1) \t\t\t\t ClifterOS Terminal Manual \n"
                    "NAME : \n "
                    "\tcursor\n"
                    "SYNOPSIS : \n "
                    "\tcursor [-t <CRSR_START> <CRSR_END>]\n"
                    "DESCRIPTION : \n "
                    "\tOptions to change cursor attributes.\n"
                    "OPTIONS : \n "
                    "\t Option Summary \n "
                    "\t\t [-t <CRSR_START> <CRSR_END>] : cursor now changes to custom type.\n "
                    "\t\t [-t block] : cursor is changed to a block cursor (START:0,END:20)\n "
                    "\t\t [-t def] : cursor changes to default underline.  (START:15,END:15)\n", 
    .cmd_opts =  cmd_cursor_opts,
    .handler = &cmd_cursor_handler,    
    .invalid_use_msg = "Invalid use of cursor command.\n"
                        "Type in cursor --help for more help.\n",
    .privilege = USER
};
