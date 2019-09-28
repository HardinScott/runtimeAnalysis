
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


extern atomic_flag aflag;

void *commandline(void *ptr) {
    char *message;
    u_int i;
    char num_str[8];
    size_t command_size;
    message = (char *) ptr;
    printf("%s \n", message);

    /* Enter multiple commands in the queue to be scheduled */
    for (i = 0; i < NUM_OF_CMD; i++) {
		
        

   } /* end for */
   printf("\nscheduler ended\n");
   
   exitQueue();//tell run to stop looking for job_queue
   atomic_flag_clear(&aflag);
   jobQueueNotEmpty();
   
}