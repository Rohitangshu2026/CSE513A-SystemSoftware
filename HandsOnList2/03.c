/*
================================================================================================
Name        : 03.c
Author      : Rohitangshu Bose
Description : Write a program to set (any one) system resource limit. Use setrlimit system call.
Date        : 1st October, 2025.
================================================================================================
*/

#include <stdio.h>
#include <sys/resource.h>
#include <errno.h>

int main()
{
    struct rlimit rlim;

    if (getrlimit(RLIMIT_FSIZE, &rlim) == -1) {
        perror("getrlimit initial");
        return 1;
    }

    if (rlim.rlim_cur == RLIM_INFINITY) {
        printf("Original Soft Limit: Unlimited\n");
    } else {
        printf("Original Soft Limit: %llu\n", (unsigned long long)rlim.rlim_cur);
    }
    
    if (rlim.rlim_max == RLIM_INFINITY) {
        printf("Original Hard Limit: Unlimited\n\n");
    } else {
        printf("Original Hard Limit: %llu\n\n", (unsigned long long)rlim.rlim_max);
    }

    rlim.rlim_cur = 1024;
    rlim.rlim_max = 2048;

    printf("New Soft Limit: %llu\n", (unsigned long long)rlim.rlim_cur);
    printf("New Hard Limit: %llu\n\n", (unsigned long long)rlim.rlim_max);

    if (setrlimit(RLIMIT_FSIZE, &rlim) == 0)
    {
        getrlimit(RLIMIT_FSIZE, &rlim);

        printf("Verified Soft Limit: %llu\n", (unsigned long long)rlim.rlim_cur);
        printf("Verified Hard Limit: %llu\n", (unsigned long long)rlim.rlim_max);
    }
    else
    {
        perror("setrlimit failed");
    }

    return 0;
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 03.c
rohit2026~$./a.out
Original Soft Limit: Unlimited
Original Hard Limit: Unlimited

New Soft Limit: 1024
New Hard Limit: 2048

Verified Soft Limit: 1024
Verified Hard Limit: 2048
================================================
*/