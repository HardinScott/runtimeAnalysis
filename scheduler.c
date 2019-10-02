
/*
 * This function simulates a terminal where users may
 * submit job_structs into a batch processing queue.
 * Note: The input parameter (i.e., *ptr) is optional.
 * If you intend to create a thread from a function
 * with input parameters, please follow this example.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "scheduler.h"
#include "jobQueue.h"
#include <stdatomic.h>
#include "commandline_parser.h"

//is done flag
extern atomic_flag aflag;
//to run in pthread in csubatch main function
void *commandline(void *ptr) {
    while(1){
		char holder[100];
		fgets(holder, 100, stdin);
		if(cmd_dispatch(holder) == 2)
		{
			break ;
		}
   }
   printf("\nscheduler ended\n");
   
   exitQueue();//tell run to stop looking for job_queue
   atomic_flag_clear(&aflag);
   jobQueueNotEmpty();
   
}
