
/*
 *
 * This program will be launched in fork_execv (see fork_execv.c).
 *
 * Compilation Instruction:
 * gcc process.c -o process
 *
 * Reference:
 * https://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1044654269&id=1043284392
 *
 */
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[] )
{
    int i = 1;
    printf("A process is running ...\n");
	sleep(3);
    argc--;

    /* Print all the arguments passed from the commandline */
    while (argc > 0) {
        printf ("Argument %d is: %s\n", i, argv[i]);
        i++;
        argc--;
    }

    return 0;
}