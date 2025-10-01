/*
======================================================================================================
Name        : 01_b.c
Author      : Rohitangshu Bose
Description : Write a separate program (for each time domain) to set a interval timer in 10s and 10ms
                b. ITIMER_VIRTUAL
Date        : 30th September, 2025.
======================================================================================================
*/

#include<stdio.h>
#include<sys/time.h>
#include<signal.h>
#include<unistd.h>

void handler(){
    printf("Timer signal received!!\n");
}

int main(){
    struct itimerval timer;
    signal(SIGVTALRM, handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10000;

    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10000;

    setitimer(ITIMER_VIRTUAL, &timer, NULL);

    while (1);
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 01_b.c
rohit2026~$./a.out   
Timer signal received!!
Timer signal received!!
Timer signal received!!
Timer signal received!!
Timer signal received!!
Timer signal received!!
Timer signal received!!
================================================
*/
