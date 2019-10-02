#ifndef _performance_h
#define _performance_h
//adds computation time
void addCPU(long int result);
//adds for turnaround
void addTurn(long int result);
//adds for average wait
void addWait(long int result);
//give rec count to div for average job
void incrementRecCount();
//sets arrive time for throughput
void setFirstArri(time_t arri);
//gets final end time for throughput
void setLastEnd(time_t end);
//sees if a job has been submitted so no div by zero
int getFirstIsSet();
//prints metrics
void printstats();

#endif
