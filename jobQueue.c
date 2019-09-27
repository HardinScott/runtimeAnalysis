/*Headers*/
#include "jobQueue.h"
#include <pthread.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*prototypes*/
static void displayJob(job_struct element);	//displays job_struct content
static void addJobWithoutLock(job_struct job); //adds job when lock has been previously acquired
static void incrementJobCountWithoutLock(); //increments job_count when lock has been previously acquired
static void decrementJobCountWithoutLock(); //decrements job_count when lock has been previously acquired
static int isEmptyWithoutLock(); //returns 1 if job_queue_buffer is empty else returns 0, use when lock previously acquired
static int isFullWithoutLock(); //returns 1 if job_queue_buffer is full else returns 0, use when lock previously acquired
static int getJobCountWithoutLock(); //returns job_count when lock has been previously acquired
static void setHeadPosWithoutLock(int headPos); //sets buf_head and ensures within range of job_queue_buffer
static void incrementHeadWithoutLock(); //increments buf_head by one, when lock has been previously acquired
static void derementHeadWithoutLock(); //decrements buf_head by one, when lock has been previously acquired
static int getHeadPosWithoutLock(); //returns buf_head when lock has been previously acquired
static job_struct getHeadElementWithoutLock(); //gets element located at buf_head, when lock has been previously acquired
static void setTailPosWithoutLock(int tailPos); //sets buf_tail and ensure within range of job_queue_buffer
static void incrementTailWithoutLock(); //increments buf_tail by one when lock has been previously acquired
static void decrementTailWithoutLock(); //decrements buf_tail by one when lock has been previously acquired
static int getTailPosWithoutLock(); //returns buf_tail when lock has been previously acquired
static job_struct getTailElementWithoutLock(); //returns element at buf_tail when lock has been acquired

/*pthread mutex and condition variables*/
pthread_mutex_t job_queue_lock;  /* Lock for critical sections */
pthread_cond_t job_buf_not_full; /* Condition variable for buf_not_full */
pthread_cond_t job_buf_not_empty; /* Condition variable for buf_not_empty */

/*Constant definitions*/
#define JOB_BUF_SIZE 10 // The size of the JOB queue
#define NUM_OF_CMD   5  // The number of submitted jobs   
#define MAX_CMD_LEN  512 // The longest commandline length



/* queue variables */
static int buf_head;
static int buf_tail;
static int job_count;
static job_struct job_queue_buffer[JOB_BUF_SIZE];

/*struct variables*/
struct job_struct;


/*jobQueue function definitions*/

/*signal functions*/
void jobQueueNotEmpty()
{
	pthread_cond_signal(&job_buf_not_empty);
}

/*initializes jobQueue variables*/
void initJobQueue()
{
	/* Initialize count, two buffer pointers */
    job_count = 0;
    buf_head = 0;
    buf_tail = 0;
}

/*initialize mutex lock and conditions*/
void initMutex()
{
	/* Initialize the lock the two condition variables */
    pthread_mutex_init(&job_queue_lock, NULL);
    pthread_cond_init(&job_buf_not_full, NULL);
    pthread_cond_init(&job_buf_not_empty, NULL);
}

/*creates a new job*/
job_struct newJob(char* job_name, int arrival_position, int execution_time, int priority, char* status)
{	
	job_struct new_job;
	new_job.job_name = job_name;
	new_job.arrival_position = arrival_position;
	new_job.execution_time = execution_time;
	new_job.priority = priority;
	new_job.status = status;
	
	return new_job;
}

/*adds job to queue*/
void addJob(job_struct job)//use when lock is not acquired
{
	/* lock the shared job queue */
    pthread_mutex_lock(&job_queue_lock);
	
	addJobWithoutLock(job);
	
    pthread_mutex_unlock(&job_queue_lock);
}

static void addJobWithoutLock(job_struct job)//For when lock has been previously acquired
{
	//wait if job queue is full
	while (isFullWithoutLock() == 1)
	{
		pthread_cond_wait(&job_buf_not_full, &job_queue_lock);
    }
	
	//
	job_queue_buffer[buf_head] = job;
	
	//increment pointer variables
	incrementJobCountWithoutLock();
	incrementHeadWithoutLock();
	
	pthread_cond_signal(&job_buf_not_empty);
	
}

/*Runs job*/
void runJob()
{
	/* lock and unlock for the shared process queue */
        pthread_mutex_lock(&job_queue_lock);
        
        while (isEmptyWithoutLock() == 1) {
            pthread_cond_wait(&job_buf_not_empty, &job_queue_lock);
        }
		
		if(isEmptyWithoutLock() == 0)
		{
			/* Run the command scheduled in the queue */
			decrementJobCountWithoutLock;
			printf("In executor: job_structQueueBuffer[%d] = %s\n", buf_tail, job_queue_buffer[buf_tail].job_name);
			
			char* args[] = {job_queue_buffer[buf_tail].job_name,NULL};
			/*
			* Note: system() function is a simple example.
			* You should use execv() rather than system() here.
			*/
			execv("./", args);

			/* Move buf_tail forward, this is a circular queue */
			incrementTailWithoutLock();
			decrementJobCountWithoutLock();
			pthread_cond_signal(&job_buf_not_full);
			/* Unlock the shared command queue */
			pthread_mutex_unlock(&job_queue_lock);
		}
}
/*
void switchJobsInQueue(int posJobA, int posJobB)
{
	pthread_mutex_lock(&job_queue_lock);
	switchJobsInQueueWithoutLock(posJobA, posJobB);
	pthread_mutex_unlock(&job_queue_lock);
}

static void switchJobsInQueueWithoutLock(int posJobA, int posJobB)
{
	job_struct temp = 
}
*/
/*increments job_count*/
void incrementJobCount()
{
	pthread_mutex_lock(&job_queue_lock);
	incrementJobCountWithoutLock();
	pthread_mutex_unlock(&job_queue_lock);
}

static void incrementJobCountWithoutLock()
{
	job_count++;
}

/*decrements job_count*/
void decrementJobCount()
{
	pthread_mutex_lock(&job_queue_lock);
	decrementJobCountWithoutLock();
	pthread_mutex_unlock(&job_queue_lock);
}

static void decrementJobCountWithoutLock()
{
	job_count--;
}

/*returns job_count*/
int getJobCount()
{

	pthread_mutex_lock(&job_queue_lock);
	int count = getJobCountWithoutLock();
	pthread_mutex_unlock(&job_queue_lock);
	
	return count;
}

static int getJobCountWithoutLock()
{
	return job_count;
}

/*checks if job_queue_buffer is empty, returns 1 for true, else 0*/
int isEmpty()
{
	pthread_mutex_lock(&job_queue_lock);
	int flag = isEmptyWithoutLock();
	pthread_mutex_unlock(&job_queue_lock);
	return flag;
}

static int isEmptyWithoutLock() //if job queue is empty returns 1 else 0
{	
	if(buf_head == buf_tail)
	{
		return 1;
	}
	
	return 0;
}

/*checks if job_queue_buffer is full, returns 1 else 0*/
int isFull() //if job queue is full returns 1 else 0
{
	pthread_mutex_lock(&job_queue_lock);
	int flag = isFullWithoutLock();
	pthread_mutex_unlock(&job_queue_lock);
	
	return flag;

}

static int isFullWithoutLock()
{
	if(job_count == JOB_BUF_SIZE)
	{
		return 1;
	}
	
	return 0;
}

/*buf_head functions*/

/*sets buf_head and ensures its between 0 - JOB_BUF_SIZE*/
void setHeadPos(int headPos)
{
	pthread_mutex_lock(&job_queue_lock);
	setHeadPosWithoutLock(headPos);
	pthread_mutex_unlock(&job_queue_lock);
}

static void setHeadPosWithoutLock(int headPos)
{
	buf_head = headPos;
	if (buf_head >= JOB_BUF_SIZE)//if exceeds buffer size sets head to 0
    {	
		buf_head = 0;
	}
	else if (buf_head < 0) // if head is below 0 sets head to end of array
	{
		buf_head = JOB_BUF_SIZE - 1;
	}
}

/*increments buf_head by one*/
void incrementHead()
{
	pthread_mutex_lock(&job_queue_lock);
	incrementJobCountWithoutLock();
	pthread_mutex_unlock(&job_queue_lock);
}

static void incrementHeadWithoutLock()
{
	setHeadPosWithoutLock(buf_head + 1);
}

/*decrements buf_head by one*/
void decrementHead()
{
	pthread_mutex_lock(&job_queue_lock);
	derementHeadWithoutLock();
	pthread_mutex_unlock(&job_queue_lock);
}

static void derementHeadWithoutLock()
{
	setHeadPosWithoutLock(buf_head - 1);
}

/*gets position of buf_head*/
int getHeadPos()
{
	pthread_mutex_lock(&job_queue_lock);
	int head = getHeadPosWithoutLock();
	pthread_mutex_unlock(&job_queue_lock);
	return head;
}

static int getHeadPosWithoutLock()
{
	return buf_head;
}

/*gets element at buf_head*/
job_struct getHeadElement()
{
	pthread_mutex_lock(&job_queue_lock);
	job_struct job = getHeadElementWithoutLock();
	pthread_mutex_unlock(&job_queue_lock);
	
	return job;
}

static job_struct getHeadElementWithoutLock()
{
	return job_queue_buffer[buf_head];
}

/*displays element at head */
void displayHead()
{
	displayJob(getHeadElement());
}


/* Tail Functions*/

/*Sets position of buf_tail and checks its between 0 - JOB_BUF_SIZE*/
void setTailPos(int tailPos) //set tail position in array
{
	pthread_mutex_lock(&job_queue_lock);
	setTailPosWithoutLock(tailPos);
	pthread_mutex_unlock(&job_queue_lock);
}

static void setTailPosWithoutLock(int tailPos)
{
	buf_tail = tailPos;
	if (buf_tail >= JOB_BUF_SIZE)//if exceeds buffer size sets head to 0
    {	
		buf_tail = 0;
	}
	else if (buf_tail < 0)
	{
		buf_tail = JOB_BUF_SIZE - 1;
	}
}

/*Increments tail by one*/
void incrementTail() //increment tail position
{
	pthread_mutex_lock(&job_queue_lock);
	incrementTailWithoutLock();
	pthread_mutex_unlock(&job_queue_lock);
}

static void incrementTailWithoutLock()
{
	setTailPosWithoutLock(buf_tail + 1);
}

/*Decrements tail by one*/
void decrementTail() //decrement tail position
{
	pthread_mutex_lock(&job_queue_lock);
	decrementJobCountWithoutLock();
	pthread_mutex_unlock(&job_queue_lock);
}

static void decrementTailWithoutLock()
{
	setTailPosWithoutLock(buf_tail - 1);
}

/*returns buf_tail position*/
int getTailPos()
{
	pthread_mutex_lock(&job_queue_lock);
	int tail = getTailPosWithoutLock();
	pthread_mutex_unlock(&job_queue_lock);
	
	return tail;
}

static int getTailPosWithoutLock()
{
	return buf_tail;
}

/*returns element at buf_tail*/
job_struct getTailElement()
{
	pthread_mutex_lock(&job_queue_lock);
	getTailElementWithoutLock();
	pthread_mutex_unlock(&job_queue_lock);
}

static job_struct getTailElementWithoutLock()
{
	return job_queue_buffer[buf_tail];
}

/*display element at tail in job_queue_buffer*/
void displayTail()
{
	displayJob(getTailElement());
}

static void displayJob(job_struct element)
{
	printf("Name: %s\nArrival Position: %d\nExecution Time: %d\nPriority: %d\nStatus: %s\n",
		element.job_name,
		element.arrival_position,
		element.execution_time,
		element.priority,
		element.status);		
}
/*
void getElementAtPos(int pos)
{
	
}

static void getElementAtPosWithoutLock(int pos)
{
	
}
*/