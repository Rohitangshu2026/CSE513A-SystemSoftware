/*
============================================================================
Name        : 29.c
Author      : Rohitangshu Bose
Description : Write a program to get scheduling policy and modify the 
              scheduling policy (SCHED_FIFO,SCHED_RR).
Date        : 7th September, 2025
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <stdlib.h>
#include <errno.h>

void display_policy(int policy) 
{
    switch (policy) 
    {
        case SCHED_OTHER:
            printf("Scheduling policy: SCHED_OTHER (normal)\n");
            break;
        case SCHED_FIFO:
            printf("Scheduling policy: SCHED_FIFO (FIFO real-time)\n");
            break;
        case SCHED_RR:
            printf("Scheduling policy: SCHED_RR (Round-Robin real-time)\n");
            break;
        default:
            printf("Scheduling policy: Unknown (%d)\n", policy);
    }
}

int main() {
    pid_t pid = getpid();  
    struct sched_param param;
    int current_policy;

    param.sched_priority = 10;

    current_policy = sched_getscheduler(pid);
    if (current_policy == -1) {
        perror("Failed to get current scheduling policy");
        return 1;
    }

    printf("Before policy change:\n");
    display_policy(current_policy);

    if (current_policy == SCHED_FIFO) 
    {
        if (sched_setscheduler(pid, SCHED_RR, &param) == -1) 
            perror("Failed to switch to SCHED_RR");
            return 1;
    } 
    else if (current_policy == SCHED_RR) 
    {
        if (sched_setscheduler(pid, SCHED_FIFO, &param) == -1) 
            perror("Failed to switch to SCHED_FIFO");
            return 1;
    } 
    else if (current_policy == SCHED_OTHER) 
    {
        if (sched_setscheduler(pid, SCHED_RR, &param) == -1) 
            perror("Failed to switch to SCHED_RR");
            return 1;
    }
    else 
    {
        fprintf(stderr, "Unknown scheduling policy\n");
        return 1;
    }

    current_policy = sched_getscheduler(pid);
    printf("After policy change:\n");
    display_policy(current_policy);

    return 0;
}

/*
================================================================================
Output:
________________________________________________________________________________
ayushi@Entropy:~/HandsOnList1$ gcc 29.c
ayushi@Entropy:~/HandsOnList1$ sudo ./a.out
[sudo] password for ayushi:
Before policy change:
Scheduling policy: SCHED_OTHER (normal)
================================================================================
*/
