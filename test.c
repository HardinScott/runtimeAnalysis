#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    time_t x;
    time_t y;
    time(&x);
    sleep(1);
    time(&y);
    double holder = (y - x) /(double) 2;
    printf("x %ld y %ld x+y %f x-y %ld\n",x,y,holder, x-y);
    return 0;
}
