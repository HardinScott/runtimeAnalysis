/*
 *
 * This sample source code demonstrates the development of
 * a batch-job_struct scheduler using pthread.
 *
 * Compilation Instruction:
 * gcc pthread_sample.c -o pthread_sample -lpthread
 *
 *  Objecties:
 * 1. To compile and run a program powered by the pthread library
 * 2. To create two concurrent threads: a scheduling thread and a dispatching thread
 * 3. To execute job_structs in the csubatch system by the dispatching thread
 * 4. To synchronize the two concurrent threads using condition variables
 *
 * How to run csubatch_sample?
 * 1. You need to compile another sample code: process.c
 * 2. The "process" program (see process.c) takes two input arguments
 * from the commandline
 * 3. In csubatch: type ./process 5 10 to submit program "process" as a job_struct.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "jobQueue.h"
#include "scheduler.h"
#include "dispatcher.h"
#include "commandline_parser.h"


typedef unsigned int u_int;

//#define LOW_ARRIVAL_RATE /* Long arrivel-time interval */
#define LOW_SERVICE_RATE   /* Long service time */

/*
 * Static commands are submitted to the job_struct queue.
 * When comment out the following macro, job_struct are submitted by users.
 */

/*
 * When a job_struct is submitted, the job_struct must be compiled before it
 * is running by the executor thread (see also executor()).
 */



int main() {
    pthread_t command_thread, executor_thread; /* Two concurrent threads */
    char *message1 = "Command Thread";
    char *message2 = "Executor Thread";
    int  iret1, iret2;

	//initialize job_struct queue
	initJobQueue();
    

    /* Create two independent threads:command and executors */
    iret1 = pthread_create(&command_thread, NULL, commandline, (void*) message1);
    iret2 = pthread_create(&executor_thread, NULL, executor, (void*) message2);

    /* Initialize the lock the two condition variables */
    pthread_mutex_init(&cmd_queue_lock, NULL);
    pthread_cond_init(&cmd_buf_not_full, NULL);
    pthread_cond_init(&cmd_buf_not_empty, NULL);

    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */
    pthread_join(command_thread, NULL);
    pthread_join(executor_thread, NULL);

    printf("command_thread returns: %d\n",iret1);
    printf("executor_thread returns: %d\n",iret1);
    exit(0);
}


