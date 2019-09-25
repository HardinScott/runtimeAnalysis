/*Functions for job_struct Queue*/
#include "jobQueue.h"
#include <pthread.h>
#include <sys/types.h>
#include <string.h>

pthread_mutex_t cmd_queue_lock;  /* Lock for critical sections */
pthread_cond_t cmd_buf_not_full; /* Condition variable for buf_not_full */
pthread_cond_t cmd_buf_not_empty; /* Condition variable for buf_not_empty */

/*Constant definitions*/
#define CMD_BUF_SIZE 10 // The size of the command queue
#define NUM_OF_CMD   5  // The number of submitted jobs   
#define MAX_CMD_LEN  512 // The longest commandline length


/* Global shared variables */
u_int buf_head;
u_int buf_tail;
u_int count;

//struct varibles
struct job_struct;



//define job_struct queue buffer
job_struct jobQueueBuffer[CMD_BUF_SIZE];


void initJobQueue()
{
	/* Initilize count, two buffer pionters */
    count = 0;
    buf_head = 0;
    buf_tail = 0;
}


job_struct newJob(char* jobName, int position, int executionTime, int priority, char* status)
{	
	job_struct newJob;
	newJob.jobName = jobName;
	newJob.position = position;
	newJob.executionTime = executionTime;
	newJob.priority = priority;
	newJob.status = status;
	
	return newJob;
}

void addJob(job_struct job)
{
	jobQueueBuffer[buf_head] = job;
}

