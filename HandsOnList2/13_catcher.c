
/*
=====================================================================================
Name        : 13_catcher.c
Author      : Rohitangshu Bose
Description : Write program that is waiting to catch SIGSTOP signal
Date        : 1st October, 2025.
=====================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void handler(int sig)
{
    printf("Signal Caught!! %d\n", sig);
    exit(0);
}

int main()
{
    printf("pid of receiver : %d\n", getpid());

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    
    sa.sa_handler = handler;
    
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }
    
    for (;;)
    {
        sleep(1);
    }
    
    return (0);
}


/*
================================================
Output:
________________________________________________
rohit2026~$gcc 13_catcher.c -o catcher.out
rohit2026~$./catcher.out                  
pid of receiver : 2548
Signal Caught!! 30
================================================
*/