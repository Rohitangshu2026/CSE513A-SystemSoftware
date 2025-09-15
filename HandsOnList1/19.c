/*
====================================================================================
Name        : 19.c
Author      : Rohitangshu Bose
Description : Write a program to find out time taken to execute getpid system call. 
              Use time stamp counter. 
Date        : 1st September, 2025
====================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <mach/mach_time.h>

#define ITERATIONS 1000000

uint64_t convert_to_nanoseconds(uint64_t elapsed) {
    static mach_timebase_info_data_t timebase_info = {0};
    if (timebase_info.denom == 0) {
        mach_timebase_info(&timebase_info);
    }
    return (elapsed * timebase_info.numer) / timebase_info.denom;
}

int main() {
    uint64_t start, end, elapsed_time;
    pid_t pid;

    start = mach_absolute_time();

    for (int i = 0; i < ITERATIONS; i++) {
        pid = getpid();
    }

    end = mach_absolute_time();
    elapsed_time = convert_to_nanoseconds(end - start) / ITERATIONS;

    printf("PID (last call): %d\n", pid);
    printf("Average time per getpid(): %llu ns\n", elapsed_time);

    return 0;
}

/*
================================================================================
Output:
________________________________________________________________________________
rohit2026~$gcc 19.c
rohit2026~$./a.out 
PID (last call): 15481
Average time per getpid(): 5 ns
================================================================================
*/

