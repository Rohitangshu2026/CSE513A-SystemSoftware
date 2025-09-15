/*
===================================================================================
Name        : 23.c
Author      : Rohitangshu Bose
Description : 23. Write a program to create a Zombie state of the running program.
Date        : 1st September, 2025
===================================================================================
*/
#include <sys/wait.h> 
#include <unistd.h>    
#include <stdio.h>     

int main()
{
    pid_t pid = fork();

    if(pid == -1) 
    {
        perror("fork failed");
        return 1;
    } 
    
	if(pid > 0)
    {
		printf("This is Parent process with PID: %d\n",getpid());

		printf("Parent going to sleep for 15s!\n");
        sleep(15);
        printf("Parent awakens!\n");

		wait(NULL);
	}
    else
    {
		printf("In Child process with PID: %d\n",getpid());

		printf("Child going to sleep for 5s!\n");
        sleep(5);
        printf("Child awakens!\n");

		printf("Child Exits!\n");
		_exit(0);
	}
	return 0;
}
/*
===============================================
Output:
_______________________________________________
rohit2026~$gcc 23.c
rohit2026~$./a.out 
This is Parent process with PID: 3466
Parent going to sleep for 15s!
In Child process with PID: 3467
Child going to sleep for 5s!
Child awakens!
Child Exits!
Parent awakens!
===============================================
*/
