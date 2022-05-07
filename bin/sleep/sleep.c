#include <misc/status_codes.h>
#include <sh/shell.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <string/string.h>
#include <sleep/sleep.h>
#include <sleep/opts/main_sleep.h>
#include <string/string.h>
#include <ctype/ctype.h>

struct cmd_opt_t* cmd_sleep_opts[] = {
  0
};

int cmd_sleep_handler(char* cmd) {
   size_t num_opts = get_opt_count(cmd);
   str_t opts[num_opts];
   get_opt(cmd,opts);
   
   if(strcmp(opts[1].str,"--help")==0) {
     printk(cmd_sleep.help);
     return STATUS_OK;
   }
   
   if(strcmp(opts[1].str,"")==0 || isdigit(opts[1].str[0])==0) {
       printk("sleep: missing operand\n");
       printk("Try 'sleep --help' for more information.\n");
       return STATUS_OK;
   }
   
   for(size_t i=0; i< (strlen(opts[1].str)-1); i++) {
        if(isdigit(opts[1].str[i])==0) {
            printk("sleep: invalid time interval %s\nTry 'sleep --help' for more information.\n", opts[1].str);
            return STATUS_OK;
        }
   }        
   
   main_sleep_opt_handler(cmd);
   
   return STATUS_OK;
}

struct cmd_t cmd_sleep = {
  .name = "sleep",
  .usage ="sleep [<s> || suffix[s,m,h,d]] [--help]",
  .help = "sleep(1) \t\t\t\t ClifterOS Terminal Manual \n"
                "NAME : \n "
                "\tsleep\n"
                "SYNOPSIS : \n "
                "\tsleep [<s> || suffix[s,m,h,d]] [--help]\n"
                "DESCRIPTION : \n "
                "\tSleeps for the number of seconds specified.\n "
                "\tAdditonal suffix may be added either s,m,h,d to specify\n "
                "\tsecond(s),minute(s),hour(s),day(s) respectively\n", 
  .cmd_opts =  cmd_sleep_opts,
  .handler = &cmd_sleep_handler,    
  .invalid_use_msg = "Invalid use of sleep command.\n"
                     "Type in sleep --help for more help.\n",
  .privilege = USER
};
