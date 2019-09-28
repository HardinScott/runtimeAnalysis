#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct{
	char* job_name;
	time_t arrival_time;
	time_t exec_time;
	time_t end_time;
}job_record_struct;

job_record_struct newRecord(char* job_name, time_t arri_t, time_t exec_t, time_t end_t)
{
	job_record_struct record;
	record.job_name = job_name;
	record.arrival_time = arri_t;
	record.exec_time = exec_t;
	record.end_time = end_t;
}
