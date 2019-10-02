#ifndef _performance_h
#define _performance_h

void addCPU(long int result);
void addTurn(long int result);
void addWait(long int result);
void incrementRecCount();
void setFirstArri(time_t arri);
void setLastEnd(time_t end);
int getFirstIsSet();

void printstats();

#endif