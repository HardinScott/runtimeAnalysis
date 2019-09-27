//Commandline_parser.h
//Header file for the commandline_parser
#ifndef _commandline_parser_h
#define _commandline_parser_h



int cmd_run(int nargs, char **args);
//ListJobQueue
int cmd_list(int nargs, char **args);
//switch the policy
int cmd_fcfs(int nargs, char **args);

int cmd_sjf(int nargs, char **args);

int cmd_priority(int nargs, char **args);

//quit and calc time,throughput etc.
int cmd_quit(int nargs, char **args);

//
int cmd_test(int nargs, char **args);

void showmenu(const char *name, const char *x[]);

int cmd_helpmenu(int n, char **a);

int cmd_dispatch(char *cmd);


#endif