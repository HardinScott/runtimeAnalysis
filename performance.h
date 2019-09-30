#ifndef _performance_h
#define _performance_h

typedef struct{
	char* job_name;
	time_t arrival_time;
	time_t exec_time;
	time_t end_time;
}job_rec_struct;

job_rec_struct newRecord(char* job_name, time_t arri_t, time_t exec_t, time_t end_t);

void insertRecord(job_rec_struct record);

#endif