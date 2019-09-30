#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "performance.h"
#define NUMBRECORDS

/*prototypes*/
static void incrementRecCount();
static float calcTurnTime();
static float calculateCPUTime();
static float calcWaitTime();
static float calcThroughput();




struct job_rec_struct;

static int numRecords = 0;

job_rec_struct records[10000];



job_rec_struct newRecord(char* job_name, time_t arri_t, time_t exec_t, time_t end_t)
{
	job_rec_struct record;
	record.job_name = job_name;
	record.arrival_time = arri_t;
	record.exec_time = exec_t;
	record.end_time = end_t;
}

void insertRecord(job_rec_struct record)
{
	records[numRecords] = record;
	incrementRecCount();
}

static void incrementRecCount()
{
	numRecords++;
}

static float calculateCPUTime()
{
	long int total = 0;
	float avg = 0.0;
	
	for( int i = 0; i < numRecords - 1; i++)
	{
		 total = (total + (records[i].end_time - records[i].exec_time));
	}
	avg = total / numRecords;
	return avg;
}

static float calcTurnTime()
{
	long int total = 0;
	float avg = 0.0;
	
	for( int i = 0; i < numRecords - 1; i++)
	{
		 total = (total + ( records[i].end_time - records[i].arrival_time));
	}
	avg = total / numRecords;
	return avg;
}

static float calcWaitTime()
{
	long int total = 0;
	float avg = 0.0;
	
	for( int i = 0; i < numRecords - 1; i++)
	{
		 total = (total + ( records[i].exec_time - records[i].arrival_time));
	}
	avg = total / numRecords;
	return avg;
}

static float calcThroughput()
{
	long int total = 0;
	float avg = 0.0;
	
	total = (total + ( records[numRecords - 1].end_time - records[0].arrival_time));

	avg = total / numRecords;
	return avg;
}




void printstats()
{
	printf("\nTotal number of jobs submitted: %d\n", numRecords);
	printf("\nAverage turnaround time: %f seconds\n", calculateCPUTime());
	printf("\nAverage CPU time: %f seconds\n", calcTurnTime());
	printf("\nAverage waiting time: %f seconds\n", calcWaitTime());
	printf("\nThroughput: %f No.//seconds\n", calcThroughput());
}


