/*
 *
 * Compilation Instruction:
 * gcc commandline_parser.c -o commandline_parser
 * ./commandline_parser
 *
 */

#include "commandline_parser.h"
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "jobQueue.h"
#include <stdatomic.h>

/* Error Code */
#define EINVAL       1
#define E2BIG        2
#define MAXJOB       100
#define MAXMENUARGS  7
//adds job to queue to run
int cmd_run(int nargs, char **args) {
    time_t arr_timep;

    if (nargs != 4) {
        printf("Usage: run <job> <time> <priority>\n");
        return EINVAL;
    }

    char *job = malloc(sizeof(char) * 254);
    int cpu_time = 0;
    int pri = 0;
	
	strcpy(job, args[1]);
    sscanf(args[2], "%d", &cpu_time);
    sscanf(args[3], "%d", &pri);

    job_struct new_job = newJob(job, 0, cpu_time, pri);

    addJob(new_job);

    printf("Job %s was submitted.\n", job);

    return 0; /* if succeed */

}
//lists all jobs
int cmd_list(int nargs, char **args){
    listJobsInQueue();
    return 0;
}
//sorts and sets all jobs added to sort by when they were added
int cmd_fcfs(int nargs, char **args){
    setSchedType(1);
    sortByPosition();
    printf("Now Sorting By FCFS, sorted %d items is in queue\n", getJobCount());
    return 0;
}
//sorts and sets all jobs added to sort by user defined cpu time

int cmd_sjf(int nargs, char **args){
    setSchedType(2);
    sortByExecTime();
    printf("Now Sorting By SJF, sorted %d items is in queue\n", getJobCount());
    return 0;
}
//sorts and sets all jobs added to sort by user defined priority

int cmd_priority(int nargs, char **args){
    setSchedType(3);
    sortByPriority();
    printf("Now Sorting By priority, sorted %d items is in queue\n", getJobCount());
    return 0;

}
//quits schedualer 
int cmd_quit(int nargs, char **args) {
    return 2;
}
//tests performance
int cmd_test(int nargs, char **args){
    if(nargs != 7) {
        printf("Usage: test <job name> <policy> <num_of_jobs> <priority_levels> <min_CPU_time> <max_CPU_time>\n");
        return EINVAL;
    }
    int noJobs = atoi(args[3]);
    if(noJobs >= JOB_BUF_SIZE){
	printf("too many jobs, defaulting to max queue size\n");
	noJobs = JOB_BUF_SIZE;
    }
    if(strcmp(args[2], "fcfs") == 0 || strcmp(args[3], "FCFS") == 0)
        setSchedType(1); 
    else if(strcmp(args[2], "sjf") == 0 || strcmp(args[3], "SJF") == 0)
	setSchedType(2);
    else if(strcmp(args[2], "priority") == 0 || strcmp(args[3], "Priority") == 0)
        setSchedType(3);


    time_t t;
    srand((unsigned) time(&t));
    int priHold = rand() % 10;
    int min = atoi(args[5]);
    int max = atoi(args[6]);
    int cpuHold = rand() % (min + max + 1);
    for(int i = 0; i < noJobs; i++){
	char *job = malloc(sizeof(char) * 254);
        strcpy(job, args[1]);

	int count = 0;
	addJob(newJob(job, count, cpuHold, priHold));
    }
    return 0;
}


//shows commands
void showmenu(const char *name, const char *x[])
{
    int ct, half, i;

    printf("\n");
    printf("%s\n", name);

    for (i=ct=0; x[i]; i++) {
        ct++;
    }
    half = (ct+1)/2;

    for (i=0; i<half; i++) {
        printf("    %-36s", x[i]);
        if (i+half < ct) {
            printf("%s", x[i+half]);
        }
        printf("\n");
    }

    printf("\n");
}
//strings to print in showmenu
static const char *helpmenu[] = {
    "[run] <job> <time> <priority>",
    "[list] List all jobs in the queue",
    "[fcfs] Choose FCFS as scheduling policy (default)",
    "[sjf]  Choose SJF as scheduling policy",
    "[pri]  Choose Priority as scheduling policy",
    "[test] Automatically execute all jobs in benchmark",
    "[quit] Exit CSUbatch",
    "[help] Print help menu",
    /* Please add more menu options below */
    NULL
};
//shows help menu
int cmd_helpmenu(int n, char **a)
{
    (void)n;
    (void)a;

    showmenu("CSUbatch help menu", helpmenu);
    return 0;
}

/*
 *  Command table.
 */
static struct {
    const char *name;
    int (*func)(int nargs, char **args);
} cmdtable[] = {
    /* commands: single command must end with \n */
    { "?\n",    cmd_helpmenu },
    { "h\n",    cmd_helpmenu },
    { "help\n",    cmd_helpmenu },
    { "r",        cmd_run },
    { "run",    cmd_run },
    { "ls\n",    cmd_list },
    { "list\n",    cmd_list },
    { "fcfs\n",    cmd_fcfs },
    { "sjf\n",    cmd_sjf },
    { "pri\n",    cmd_priority },
    { "test",     cmd_test},
    { "q\n",    cmd_quit },
    { "quit\n",    cmd_quit },
    /* Please add more operations below. */
    {NULL, NULL}
};

/*
 * Process a single command typed by user, invoke the function pointer.
 */

int cmd_dispatch(char *cmd)
{
    time_t beforesecs, aftersecs, secs;
    u_int32_t beforensecs, afternsecs, nsecs;
    char *args[MAXMENUARGS];
    int nargs=0;
    char *word;
    char *context;
    int i, result;
/**
strtok_r() - parsing a string into a sequence of tokens.
strtok_r() example.
// Returns first token
    char* token = strtok(str, "-");

    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, "-");
    }
**/
    for (word = strtok_r(cmd, " ", &context);
         word != NULL;
         word = strtok_r(NULL, " ", &context)) {

        if (nargs >= MAXMENUARGS) {
            printf("Command line has too many words\n");
            return E2BIG;
        }
        args[nargs++] = word;
    }

    if (nargs==0) {
        return 0;
    }
    /*fuction pointer*/
    /**
int strcmp (const char* str1, const char* str2);
0	if both strings are identical (equal)
negative	if the ASCII value of first unmatched character is less than second.
positive integer	if the ASCII value of first unmatched character is greater than second.
    **/

    //Step 1: Check if the sumbmitted command is valid or not by using assert().
    //if valid, invoke the function through the function pointers within the cmd_table
    for (i=0; cmdtable[i].name; i++) {
        if (*cmdtable[i].name  && !strcmp(args[0], cmdtable[i].name)) {
            assert(cmdtable[i].func!=NULL);

    //Step 2: Call function through the cmd_table
            result = cmdtable[i].func(nargs, args);
			return result;
            
        }
    }
	
    printf("%s: Command not found\n", args[0]);
    return EINVAL;
}

