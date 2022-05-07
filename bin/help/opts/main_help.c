#include <misc/status_codes.h>
#include <string/string.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <sh/shell.h>
#include <stdlib/stdlib.h>
#include <stdio/stdio.h>
#include <help/help.h>
#include <help/opts/help_cmd_opt.h>

int main_help_opt_handler(char *cmd) {
   size_t num_opts = get_opt_count(cmd);
   str_t opts[num_opts];
   get_opt(cmd,opts);
   
   if(strcmp(opts[1].str,"-cmd")==0) {
      if(strcmp(opts[2].str,"--help")==0)
         printk(cmd_help_opt_cmd.help);
      else   
         cmd_help_opt_cmd.handler(cmd);
   }
   else if(strcmp(opts[1].str , "--help")==0) {
      printk(cmd_help.help);
   }
   else {
      printk(cmd_help.invalid_use_msg);
   }
   
   return STATUS_OK;
}
