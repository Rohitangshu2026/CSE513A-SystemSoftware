/*
================================================================================
Name        : 28.c
Author      : Rohitangshu Bose
Description : Write a program to get maximum and minimum real time priority.
Date        : 1st September, 2025
================================================================================
*/

#include <stdio.h>
#include <sched.h>

int main() {
    int minPriority, maxPriority;

    maxPriority = sched_get_priority_max(SCHED_RR);
    if (maxPriority == -1) 
    {
        perror("Failed to get maximum priority");
        return 0;
    }

    printf("Maximum Priority: %d\n", maxPriority);

    minPriority = sched_get_priority_min(SCHED_RR);
    if (minPriority == -1) 
    {
        perror("Failed to get minimum priority");
        return 0;
    }
    printf("Minimum Priority: %d\n", minPriority);

    return 0;
}

/*
==================================================
Output:
__________________________________________________
rohit2026~$gcc 28.c
rohit2026~$./a.out 
Maximum Priority: 47
Minimum Priority: 15
=================================================
*/