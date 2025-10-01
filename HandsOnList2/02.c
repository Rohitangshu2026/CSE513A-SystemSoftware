/*
======================================================================================================
Name        : 02.c
Author      : Rohitangshu Bose
Description : Write a program to print the system resource limits. Use getrlimit system call.
Date        : 1st October, 2025.
======================================================================================================
*/

#include<stdio.h>
#include<sys/resource.h>

int main()
{
	struct rlimit limit;

	if(getrlimit(RLIMIT_AS, &limit) != -1)
	{
		printf("Virtual memory............\n");
		printf("Soft Limit :  %llu\n", limit.rlim_cur);
		printf("Hard Limit :  %llu\n", limit.rlim_max);
	}
	if (getrlimit(RLIMIT_CORE, &limit) != -1)
	{
		printf("Core file..................\n");
		printf("Soft Limit :  %llu\n", limit.rlim_cur);
		printf("Hard Limit :  %llu\n", limit.rlim_max);
	}
	if (getrlimit(RLIMIT_CPU, &limit) != -1)
	{
		printf("CPU time...................\n");
		printf("Soft Limit :  %llu\n", limit.rlim_cur);
		printf("Hard Limit :  %llu\n", limit.rlim_max);
	}
	if (getrlimit(RLIMIT_DATA, &limit) != -1)
	{
		printf("Data segment size...........\n");
		printf("Soft Limit :  %llu\n", limit.rlim_cur);
		printf("Hard Limit :  %llu\n", limit.rlim_max);
	}
	if (getrlimit(RLIMIT_FSIZE, &limit) != -1)
	{
		printf("File size...................\n");
		printf("Soft Limit :  %llu\n", limit.rlim_cur);
		printf("Hard Limit :  %llu\n", limit.rlim_max);
	}
	
	if (getrlimit(RLIMIT_MEMLOCK, &limit) != -1)
	{
		printf("Memory lock size...........\n");
		printf("Soft Limit :  %llu\n", limit.rlim_cur);
		printf("Hard Limit :  %llu\n", limit.rlim_max);
	}

	if (getrlimit(RLIMIT_NOFILE, &limit) != -1)
	{
		printf("Number of file descriptors.\n");
		printf("Soft Limit :  %llu\n", limit.rlim_cur);
		printf("Hard Limit :  %llu\n", limit.rlim_max);
	}
	if (getrlimit(RLIMIT_NPROC, &limit) != -1)
	{
		printf("Number of process..........\n");
		printf("Soft Limit :  %llu\n", limit.rlim_cur);
		printf("Hard Limit :  %llu\n", limit.rlim_max);
	}
	if (getrlimit(RLIMIT_STACK, &limit) != -1)
	{
		printf("Stack......................\n");
		printf("Soft Limit :  %llu\n", limit.rlim_cur);
		printf("Hard Limit :  %llu\n", limit.rlim_max);
	}

	return(0);
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 02.c
rohit2026~$./a.out
Virtual memory............
Soft Limit :  9223372036854775807
Hard Limit :  9223372036854775807
Core file..................
Soft Limit :  0
Hard Limit :  9223372036854775807
CPU time...................
Soft Limit :  9223372036854775807
Hard Limit :  9223372036854775807
Data segment size...........
Soft Limit :  9223372036854775807
Hard Limit :  9223372036854775807
File size...................
Soft Limit :  9223372036854775807
Hard Limit :  9223372036854775807
Memory lock size...........
Soft Limit :  9223372036854775807
Hard Limit :  9223372036854775807
Number of file descriptors.
Soft Limit :  256
Hard Limit :  9223372036854775807
Number of process..........
Soft Limit :  2666
Hard Limit :  4000
Stack......................
Soft Limit :  8372224
Hard Limit :  67092480
================================================
*/
