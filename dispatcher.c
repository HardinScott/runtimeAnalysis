/*
 * This function simulates a server running job_structs in a batch mode.
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
#include "dispatcher.h"
#include "jobQueue.h"
#include <stdatomic.h>
#include <stdbool.h>

extern atomic_flag aflag;

void *executor(void *ptr) {
    char *message;
    u_int i;

    message = (char *) ptr;
    printf("%s \n", message);

    do{
        printf("In executor: count = %d\n", getJobCount());
		
		runJob();
		
    }while(atomic_flag_test_and_set(&aflag));
	
	while(isEmpty() == 0)
	{
		printf("Jobs Left Before Exit: %d\n", getJobCount()); 
		runJob();
	}
}