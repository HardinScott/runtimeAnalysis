#include <stdio.h>
#include <stdlib.h>
#include "jobQueue.h"

int getInput(){
    int MAX_INPUT;
    char str[MAX_INPUT];
    fgets(str, MAX_INPUT, stdin);
    printf("%s \n", str);
    return 0;
}

int main(){
    getInput();
    return 0;
}
