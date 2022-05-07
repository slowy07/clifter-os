#include <stddef.h>
#include <stdint.h>
#include <unistd/unistd.h>
#include <misc/status_codes.h>
#include <sh/shell.h>
#include <stdio/stdio.h>
#include <string/string.h>



// handles help -cmd <options>
int cmd_help_opt_cmd_handler(char* cmd) {
   size_t num_opts = get_opt_count(cmd);
   str_t opts[num_opts];
   get_opt(cmd,opts);
   
   char* __user_cmd = opts[2].str;
   int __found__user_cmd = 0;
   
   for(int i=0; cmds[i]; i++) {
       if(strcmp(cmds[i]->name,__user_cmd)==0) {
         printk(cmds[i]->help);
         __found__user_cmd=1;
       }
   }
   
   if(__found__user_cmd == 0)
       printk("Command Not Found. type in command help for listings of command\n");
  
   return STATUS_OK;
}

struct cmd_opt_t cmd_help_opt_cmd = {
    .help =  "help(1) \t\t\t\t ClifterOS Terminal Manual \n"
                "NAME : \n "
                "\thelp -cmd\n"
                "SYNOPSIS : \n "
                "\thelp [-cmd <cmd_name>]\n"
                "DESCRIPTION : \n "
                "\tCalls help handler for command name\n "
                "\tif command dosent exist notifies that that\n "
                "\tcommand doesnt exit.\n"
                "OPTIONS : \n "
                "\t Option Summary \n "
                "\t\t[-cmd <cmd_name>] : calls help handler of command name\n",
        .cmd_opt_name = "-cmd" ,
        .handler = &cmd_help_opt_cmd_handler,
        .invalid_use_msg = "Invalid Use of -cmd option. Use command help --cmd --help for instructions\n"
                           "on how to use the clear command\n"
};
