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

void *executor(void *ptr) {
    char *message;
    u_int i;

    message = (char *) ptr;
    printf("%s \n", message);

    for (i = 0; i < NUM_OF_CMD; i++) {
        /* lock and unlock for the shared process queue */
        pthread_mutex_lock(&cmd_queue_lock);
        printf("In executor: count = %d\n", count);
        while (count == 0) {
            pthread_cond_wait(&cmd_buf_not_empty, &cmd_queue_lock);
        }

        /* Run the command scheduled in the queue */
        count--;
        printf("In executor: job_structQueueBuffer[%d] = %s\n", buf_tail, jobQueueBuffer[buf_tail].jobName);

        /*
         * Note: system() function is a simple example.
         * You should use execv() rather than system() here.
         */
        system(jobQueueBuffer[buf_tail].jobName);
        /* Free the dynamically allocated memory for the buffer */
        //free(job_structQueueBuffer[buf_tail]);

        /* Move buf_tail forward, this is a circular queue */
        buf_tail++;
        if (buf_tail == CMD_BUF_SIZE)
            buf_tail = 0;

        pthread_cond_signal(&cmd_buf_not_full);
        /* Unlok the shared command queue */
        pthread_mutex_unlock(&cmd_queue_lock);
    } /* end for */
}