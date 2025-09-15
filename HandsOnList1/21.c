/*
=====================================================================================================
Name        : 21.c
Author      : Rohitangshu Bose
Description : Write a program, call fork and print the parent and child process id.
Date        : 1st September, 2025
=====================================================================================================
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>  

int main()
{
	if(!fork())
    {
		printf("Child PID: %d\n",getpid());
		printf("Parent PID: %d\n",getppid());
	}
	return 0;
}


/*
===============================================
Output:
_______________________________________________
rohit2026~$gcc 21.c
rohit2026~$./a.out 
Child PID: 3249
Parent PID: 3248
===============================================
*/
