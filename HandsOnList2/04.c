/*
===============================================================================
Name        : 04.c
Author      : Rohitangshu Bose
Description : Write a program to measure how much time is taken to execute 100 
              getppid ( ) system call. Use time stamp counter.
Date        : 29th September, 2025
===============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <mach/mach_time.h>

#define ITERATIONS 100

#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main() {
    clock_t start, end;
    pid_t ppid;

    start = clock();

    for (int i = 0; i < ITERATIONS; i++) {
        ppid = getppid();
    }

    end = clock();
    double duration = (((double)(end - start)) / CLOCKS_PER_SEC) * 1e9;

    printf("PPID (last call): %d\n", ppid);
    printf("Time taken for 100 getppid() calls: %.0f ns\n", duration);
    return 0;
}

/*
===================================================================
Output:
___________________________________________________________________
rohit2026~$gcc 04.c
rohit2026~$./a.out 
PPID (last call): 2044
Time taken for 100 getppid() calls: 22000 ns
====================================================================
*/
