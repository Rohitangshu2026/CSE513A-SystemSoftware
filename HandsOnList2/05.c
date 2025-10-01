/*
======================================================================================================
Name        : 05.c
Author      : Rohitangshu Bose
Description : Write a program to print the system limitation of
                a. maximum length of the arguments to the exec family of functions.
                b. maximum number of simultaneous process per user id.
                c. number of clock ticks (jiffy) per second.
                d. maximum number of open files
                e. size of a page
                f. total number of pages in the physical memory
                g. number of currently available pages in the physical memory.
Date        : 1st October, 2025.
======================================================================================================
*/
#include<stdio.h>
#include<unistd.h>

int main()
{
    printf("System Limitations...........................................\n");
    printf("Maximum arguments length to  exec family functions: %ld\n", sysconf(_SC_ARG_MAX));
    printf("Maximum simultaneous processes per user id: %ld\n", sysconf(_SC_CHILD_MAX));
    printf("Maximum clock ticks (jiffy) per second: %ld\n", sysconf(_SC_CLK_TCK));
    printf("Maximum open files : %ld\n", sysconf(_SC_OPEN_MAX));
    printf("Maximum size of a page(in B): %ld\n", sysconf(_SC_PAGE_SIZE));
    printf("Total pages in physical memory: %ld\n", sysconf(_SC_PHYS_PAGES));
    return (0);
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 05.c
rohit2026~$./a.out 
System Limitations...........................................
Maximum arguments length to  exec family functions: 1048576
Maximum simultaneous processes per user id: 2666
Maximum clock ticks (jiffy) per second: 100
Maximum open files : 256
Maximum size of a page(in B): 16384
Total pages in physical memory: 1048576
================================================
*/