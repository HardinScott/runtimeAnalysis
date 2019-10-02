#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "performance.h"
#define NUMBRECORDS

/*prototypes*/
static double calculateCPUTime();
static double calcTurnTime();
static double calcWaitTime();
static long int calcThroughput();
static void setFirstIsSet();
static int firstIsSet = 0; //if firstArri is set then 1 else 0
static int numRecords = 0;

time_t cpuTotal, turnTotal, waitTotal, firstArri, lastEnd;





void incrementRecCount()
{
	
	numRecords++;
}

void addCPU(time_t result)
{
	cpuTotal += result;
}

void addTurn(time_t  result)
{
	turnTotal += result;
}

void setFirstArri(time_t arri)
{
	firstArri = arri;

	setFirstIsSet();

}

static void setFirstIsSet()
{
	firstIsSet = 1;
}

int getFirstIsSet()
{
	return firstIsSet;
}

void setLastEnd(time_t end)
{
	lastEnd = end;
}

void addWait(time_t  result)
{
	waitTotal += result;
}

static double calculateCPUTime()
{
	double avg = 0.0;
	if(numRecords != 0)
	{
		avg = cpuTotal / (double) numRecords;
	}
	return avg;
}

static double calcTurnTime()
{
	double avg = 0.0;
	if(numRecords != 0)
	{
		avg = turnTotal / (double) numRecords;
	}
	return avg;
}

static double calcWaitTime()
{
	double avg = 0.0;
	
	if(numRecords != 0)
	{
		avg = cpuTotal / (double) numRecords;
	}
	return avg;
}

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




void printstats()
{
	
	printf("\nTotal number of jobs submitted: %d\n", numRecords);
	printf("Average CPU time: %.2f seconds\n", calculateCPUTime());
	printf("Average Turnaround time: %.2f seconds\n", calcTurnTime());
	printf("Average Waiting time: %.2f seconds\n", calcWaitTime());
	printf("Throughput: %ld No.//seconds\n", calcThroughput());
}


