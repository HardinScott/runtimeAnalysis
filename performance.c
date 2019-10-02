#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "performance.h"
#define NUMBRECORDS

/*prototypes*/
//final cpu time
static double calculateCPUTime();
//calculates turnaround time
static double calcTurnTime();
//calculaes wait time
static double calcWaitTime();
//calculates throughput for jobs
static long int calcThroughput();
//sets when first job so no div by zero
static void setFirstIsSet();
static int firstIsSet = 0; //if firstArri is set then 1 else 0
//total num of jobs
static int numRecords = 0;

time_t cpuTotal, turnTotal, waitTotal, firstArri, lastEnd;




//counts num of jobs
void incrementRecCount()
{
	
	numRecords++;
}
//adds to cpu time to calc final avg cpu time
void addCPU(time_t result)
{
	cpuTotal += result;
}
//increases total time to calc throughput
void addTurn(time_t  result)
{
	turnTotal += result;
}
//sets first arrival time for throuhput
void setFirstArri(time_t arri)
{
	firstArri = arri;

	setFirstIsSet();

}
//sets if a job is run so no div by zero
static void setFirstIsSet()
{
	firstIsSet = 1;
}
//sees if a job has been run
int getFirstIsSet()
{
	return firstIsSet;
}
//sets final jobs final time for turnaround
void setLastEnd(time_t end)
{
	lastEnd = end;
}
//caluclates wait time
void addWait(time_t  result)
{
	waitTotal += result;
}
//calcualtes average cpu time
static double calculateCPUTime()
{
	double avg = 0.0;
	if(numRecords != 0)
	{
		avg = cpuTotal / (double) numRecords;
	}
	return avg;
}
//calculates average turnaround
static double calcTurnTime()
{
	double avg = 0.0;
	if(numRecords != 0)
	{
		avg = turnTotal / (double) numRecords;
	}
	return avg;
}
//calcualtes average wait time
static double calcWaitTime()
{
	double avg = 0.0;
	
	if(numRecords != 0)
	{
		avg = cpuTotal / (double) numRecords;
	}
	return avg;
}
// calcualtes final throughput
static long int calcThroughput()
{
	if(numRecords != 0)
	{
		return lastEnd - firstArri;
	}
	else
	{
		return 0;
	}
	
}



//prints final metrics
void printstats()
{
	
	printf("\nTotal number of jobs submitted: %d\n", numRecords);
	printf("Average CPU time: %.2f seconds\n", calculateCPUTime());
	printf("Average Turnaround time: %.2f seconds\n", calcTurnTime());
	printf("Average Waiting time: %.2f seconds\n", calcWaitTime());
	printf("Throughput: %ld No.//seconds\n", calcThroughput());
}


