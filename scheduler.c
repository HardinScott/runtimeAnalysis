
/*
 * This function simulates a terminal where users may
 * submit jobs into a batch processing queue.
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

void *commandline(void *ptr) {
    char *message;
    struct JOB temp_cmd;
    u_int i;
    char num_str[8];
    size_t command_size;

    message = (char *) ptr;
    printf("%s \n", message);

    /* Enter multiple commands in the queue to be scheduled */
    for (i = 0; i < NUM_OF_CMD; i++) {
        /* lock the shared command queue */
        pthread_mutex_lock(&cmd_queue_lock);

        printf("In commandline: count = %d\n", count);
        while (count == CMD_BUF_SIZE) {
            pthread_cond_wait(&cmd_buf_not_full, &cmd_queue_lock);
        }
	pthread_mutex_unlock(&cmd_queue_lock);

        printf("Please submit a batch processing job:\n");
        pthread_mutex_unlock(&cmd_queue_lock);

        printf("Please submit a batch processing job:\n");
        printf(">");
        temp_cmd = newJob("./process", 10, 10, 10);//create job
        //getline(&temp_cmd, &command_size, stdin);
        pthread_mutex_lock(&cmd_queue_lock);
        jobQueueBuffer[buf_head]= temp_cmd;

        printf("In commandline: jobQueueBuffer[%d] = %s\n", buf_head, jobQueueBuffer[buf_head].jobName);

        count++;

        /* Move buf_head forward, this is a circular queue */
        buf_head++;
        if (buf_head == CMD_BUF_SIZE)
            buf_head = 0;

        pthread_cond_signal(&cmd_buf_not_empty);
        /* Unlok the shared command queue */
        pthread_mutex_unlock(&cmd_queue_lock);

    } /* end for */
}