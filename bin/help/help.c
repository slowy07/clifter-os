#include <misc/status_codes.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <help/opts/help_cmd_opt.h>
#include <help/opts/main_help.h>

struct cmd_opt_t* cmd_help_opts[] = {
  &cmd_help_opt_cmd
  ,0
};

int cmd_help_handler(char* cmd) {
   size_t num_opts = get_opt_count(cmd);
   if(num_opts == 1) {
      printk("ClifterOS Shell. Type in \"<cmd_name> --help\" for more help on that command\n");
      printk("or \"help -cmd <cmd_name>\"\n\n");
      printk("Commands\n");
      printk("--------\n");
      for(int i=0; cmds[i]; i++)
        printk("%d : %s\n",i,cmds[i]->name);
      return STATUS_OK;
   }
   
   main_help_opt_handler(cmd);
   
   return STATUS_OK;
}

struct cmd_t cmd_help = {
  .name = "help",
  .usage ="help [-cmd <cmd_name>]",
  .help = "help(1) \t\t\t\t ClifterOS Terminal Manual \n"
                "NAME : \n "
                "\thelp\n"
                "SYNOPSIS : \n "
                "\thelp [-cmd <cmd_name>]\n"
                "DESCRIPTION : \n "
                "\tLists out all commands if called with no options\n "
                "\tbut if called with -cmd option calls help handler\n "
                "\tfor that command.\n"
                "MORE HELP : \n "
                "\t[help -cmd --help] for help on -cmd option\n",   
  .cmd_opts =  cmd_help_opts,
  .handler = &cmd_help_handler,    
  .invalid_use_msg = "Invalid use of help command.\n"
                     "Type in help --help for more help.\n",
  .privilege = USER
};
