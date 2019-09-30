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

int cmd_list(int nargs, char **args){
    listJobsInQueue();
    return 0;
}

int cmd_fcfs(int nargs, char **args){
    setSchedType(1);
    sortByPosition();
    printf("Now Sorting By FCFS, sorted %d items is in queue\n", getJobCount());
    return 0;
}

int cmd_sjf(int nargs, char **args){
    setSchedType(2);
    sortByExecTime();
    printf("Now Sorting By SJF, sorted %d items is in queue\n", getJobCount());
    return 0;
}

int cmd_priority(int nargs, char **args){
    setSchedType(3);
    sortByPriority();
    printf("Now Sorting By priority, sorted %d items is in queue\n", getJobCount());
    return 0;

}

int cmd_quit(int nargs, char **args) {
    exit(0);
}

int cmd_test(int nargs, char **args){
    if(nargs != 7) {
        printf("Usage: test <benchmark> <policy> <num_of_jobs> <priority_levels> <min_CPU_time> <max_CPU_time>\n");
        return EINVAL;
    }
    printf("you submitted command:cmd_test\n" );
/*
    if(strcmp(args[2], "fcfs") == 0 || strcmp(args[3], "FCFS") == 0)
        scheduling_policy = FCFS;
    else if(strcmp(args[2], "sjf") == 0 || strcmp(args[3], "SJF") == 0)
        scheduling_policy = SJF;
    else if(strcmp(args[2], "priority") == 0 || strcmp(args[3], "Priority") == 0)
        scheduling_policy = Priority;

    int job_size;
    sscanf(args[3], "%d", &job_size);
    int pri_level;
    sscanf(args[4], "%d", &pri_level);
    int min_cpu_time;
    sscanf(args[5], "%d", &min_cpu_time);
    int max_cpu_time;
    sscanf(args[6], "%d", &max_cpu_time);


    time_t t;
    time_t arr_timep;
    srand(time(&t));

    FILE *workload_file;
    workload_file = fopen("workload.txt", "r");
    if(workload_file == 0){
        printf("Could not open the workload file: workload.txt\n");
        return -1;
    }
    char *rate = malloc(sizeof(char) * 5);
    size_t r_len = 0;

    getline(&rate, &r_len, workload_file);

    int sub_rate = 0;
    sscanf(rate, "%d",&sub_rate);

    FILE *file;
    char *file_name;
    file_name = malloc(sizeof(char) * strlen(args[2]));
    strcpy(file_name, args[1]);

    file = fopen(file_name, "r");
    if(file == 0){
        printf("Could not open the benchmark: %s\n", file_name);
        return -1;
    }

    else{
        for(int i = 0; i < job_size; i++){
            JobData new_job = JobData_defult;
            char* job_name = malloc(sizeof(char) * 10);
            size_t len = 0;

            getline(&job_name, &len, file);
            if(i != job_size - 1)
                job_name[strlen(job_name) - 1] = 0;
            strcat(new_job.name, job_name);
            new_job.priority = (rand() % (pri_level - 1)) + 1;
            new_job.CPU_time = (rand() % (max_cpu_time - min_cpu_time)) + min_cpu_time;
            arr_timep = time(NULL);
            new_job.arrival_time = arr_timep;

            InsertNewJob(new_job);
            sleep(sub_rate);
        }
    }
    fclose(file);

    printf("Total number of jobs in the queue: %d\n", job_size);
    printf("Scheduling Policy: %s\n", policy_name[scheduling_policy]);
    ListJobQueue();
*/
    return 0;
}


int cmd_auto(int nargs, char **args){
    if(nargs != 4) {
        printf("Usage: auto <list> <policy> <num_of_jobs>\n");
        return EINVAL;
    }
    printf("you submitted command:cmd_auto\n" );
/*
    if(strcmp(args[2], "fcfs") == 0 || strcmp(args[3], "FCFS") == 0)
        scheduling_policy = FCFS;
    else if(strcmp(args[2], "sjf") == 0 || strcmp(args[3], "SJF") == 0)
        scheduling_policy = SJF;
    else if(strcmp(args[2], "priority") == 0 || strcmp(args[3], "Priority") == 0)
        scheduling_policy = Priority;

    int job_size;
    sscanf(args[3], "%d", &job_size);

    time_t t;
    time_t arr_timep;
    size_t r_len = 0;

    FILE *workload_file;
    workload_file = fopen("workload.txt", "r");
    if(workload_file == 0){
        printf("Could not open the workload file: workload.txt\n");
        return -1;
    }

    char *rate = malloc(sizeof(char) * 5);
    getline(&rate, &r_len, workload_file);

    int sub_rate = 0;
    sscanf(rate, "%d",&sub_rate);

    FILE *file;
    char *file_name;
    file_name = malloc(sizeof(char) * strlen(args[2]));
    strcpy(file_name, args[1]);
    size_t len = 0;
    file = fopen(file_name, "r");

    if(file == 0){
        printf("Could not open the list: %s\n", file_name);
        return -1;
    }

    else{
        for(int i = 0; i < job_size; i++){
            JobData new_job = JobData_defult;

            char *job_name = malloc(sizeof(char) * 10);
            char *job_time = malloc(sizeof(char) * 10);
            char *job_prio = malloc(sizeof(char) * 10);
            int job_t = 0;
            int job_pri = 0;

            getline(&job_name, &len, file);
            if(i != job_size * 3 - 1)
                job_name[strlen(job_name) - 1] = 0;
            strcat(new_job.name, job_name);

            getline(&job_time, &len, file);
            if(i != job_size * 3 - 1)
                job_name[strlen(job_name) - 1] = 0;
            sscanf(job_time, "%d",&new_job.CPU_time);

            getline(&job_prio, &len, file);
            if(i != job_size * 3 - 1)
                job_name[strlen(job_name) - 1] = 0;
            sscanf(job_prio, "%d",&new_job.priority);

            arr_timep = time(NULL);
            new_job.arrival_time = arr_timep;

            InsertNewJob(new_job);
            sleep(sub_rate);
        }
    }
    fclose(file);

    printf("Total number of jobs in the queue: %d\n", job_size);
    printf("Scheduling Policy: %s\n", policy_name[scheduling_policy]);
    ListJobQueue();
*/
    return 0;
}

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

static const char *helpmenu[] = {
    "[run] <job> <time> <priority>",
    "[list] List all jobs in the queue",
    "[fcfs] Choose FCFS as scheduling policy (default)",
    "[sjf]  Choose SJF as scheduling policy",
    "[pri]  Choose Priority as scheduling policy",
    "[test] Automatically execute all jobs in benchmark",
    "[auto] Automatically execute all jobs in list",
    "[quit] Exit CSUbatch",
    "[help] Print help menu",
    /* Please add more menu options below */
    NULL
};

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
    {"auto",        cmd_auto},
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

