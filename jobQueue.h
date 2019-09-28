#ifndef _jobQueue_h
#define _jobQueue_h

#include <pthread.h>
#include <sys/types.h>
#include <time.h>

//refacter so that scheduler does not need any of this!!!
#define JOB_BUF_SIZE 10 // The size of the JOB queue
#define NUM_OF_CMD   5  // The number of submitted jobs   
#define MAX_CMD_LEN  512 // The longest commandline length

//sched value holder
//1 is FCFS
//2 is SJF
//3 is Priority
int schedType = 1;

//sched functions
void getSchedType();
void setSchedType(int type);

//struct variables
typedef struct{
	char* job_name;
	int arrival_position;
	int execution_time;
	int priority;
	char* status; //change status function needed in jobQueue.c
	time_t arrival_time;
}job_struct;


/*Functions*/

/*Initialize Functions*/
void initJobQueue(); //initializes job_count, buf_head, and buf_tail
void initMutex(); //initialize mutex lock and conditions

/*Job Create,Add and Run functions*/
job_struct newJob(char* job_name, int arrival_position, int execution_time, int priority);

void addJob(job_struct job); //adds job to job queue

void runJob(); //run job from tail of job queue

void jobQueueNotEmpty();

void sortByPosition();

void sortByExecTime();

void sortByPriority();

void listJobsInQueue();

/*job count functions*/
void incrementJobCount(); //decrements job_count by 1

void decrementJobCount(); //increments job_count by 1

int getJobCount(); //returns job_count

int isEmpty(); //if job queue is empty returns 1 else 0

int isFull(); //if job queue is full returns 1 else 0

job_struct getElementAtPos(int pos); //returns element at pos

void exitQueue(); //set exitQueueFlag to 1 don't wait for job_buf_not_empty in run

static void switchJobsInQueueWithoutLock(int posJobA, int posJobB); //swaps elements in job queue at position a and b

/*head functions*/

void setHeadPos(int headPos); //sets position of buf_head. maintains within range of job_queue_buffer < 0 to JOB_BUF_SIZE - 1, > JOB_BUF_SIZE to 0

void incrementHead(); //increments buf_head by 1. maintains within range of job_queue_buffer through setHeadPos

void decrementHead();//decrements buf_head by 1. maintains within range of job_queue_buffer through setHeadPos

int getHeadPos(); //returns buf_head

job_struct getHeadElement(); //returns element at buf_head

void displayHead(); //displays information for element at buf_head


/* Tail Functions*/
void setTailPos(int tailPos); //sets position of buf_tail. maintains within range of job_queue_buffer < 0 to JOB_BUF_SIZE - 1, > JOB_BUF_SIZE to 0

void incrementTail(); //increments buf_head by 1. maintains within range of job_queue_buffer through setTailPos

void decrementTail(); //decrements buf_head by 1. maintains within range of job_queue_buffer through setTailPos

int getTailPos(); //returns buf_tail

job_struct getTailElement(); //returns element at buf_tail

void displayTail(); //displays informatino for element at buf_tail



#endif
