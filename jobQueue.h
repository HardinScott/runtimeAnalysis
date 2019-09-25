#ifndef _jobQueue_h
#define _jobQueue_h

#include <pthread.h>
#include <sys/types.h>

//pthreads mutex and conditions
extern pthread_mutex_t cmd_queue_lock;  // Lock for critical sections
extern pthread_cond_t cmd_buf_not_full; // Condition variable for buf_not_full 
extern pthread_cond_t cmd_buf_not_empty; // Condition variable for buf_not_empty




//definitions for job_struct queue
#define CMD_BUF_SIZE 10 // The size of the command queue
#define NUM_OF_CMD   5  // The number of submitted job_structs   
#define MAX_CMD_LEN  512 // The longest commandline length


//struct definitions
typedef struct{
	char* jobName;
	int position;
	int executionTime;
	int priority;
	char* status;
}job_struct;


// Global shared variables 
extern u_int buf_head;
extern u_int buf_tail;
extern u_int count;

extern job_struct jobQueueBuffer[];

//functions
void initJobQueue();

job_struct newJob(char* jobName, int position, int executionTime, int priority, char* status);

#endif