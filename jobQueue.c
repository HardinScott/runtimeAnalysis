/*Functions for Job Queue*/
#include "jobQueue.h"
#include <pthread.h>
#include <sys/types.h>

pthread_mutex_t cmd_queue_lock;  /* Lock for critical sections */
pthread_cond_t cmd_buf_not_full; /* Condition variable for buf_not_full */
pthread_cond_t cmd_buf_not_empty; /* Condition variable for buf_not_empty */


#define CMD_BUF_SIZE 10 // The size of the command queue
#define NUM_OF_CMD   5  // The number of submitted jobs   
#define MAX_CMD_LEN  512 // The longest commandline length


/* Global shared variables */
u_int buf_head;
u_int buf_tail;
u_int count;

//struct varibles
struct JOB;

//define job queue buffer
struct JOB jobQueueBuffer[CMD_BUF_SIZE];


void initJobQueue()
{
	/* Initilize count, two buffer pionters */
    count = 0;
    buf_head = 0;
    buf_tail = 0;
}


struct JOB newJob(char* jobName, int position, int executionTime, int priority)
{	
	struct JOB newJob;
	newJob.jobName = jobName;
	newJob.position = position;
	newJob.executionTime =executionTime;
	newJob.priority = priority;
	
	return newJob;
}

