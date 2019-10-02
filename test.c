#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    time_t x;
    time_t y;
    time(&x);
    sleep(2);
    time(&y);
    printf("x %ld y %ld x+y %ld\n",x,y,x-y/2);
    return 0;
}
