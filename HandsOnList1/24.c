/*
===========================================================
Name        : 24.c
Author      : Rohitangshu Bose
Description : Write a program to create an orphan process.
Date        : 1st September, 2025
===========================================================
*/

#include <unistd.h>   
#include <stdio.h>    
#include <stdlib.h>   

int main() 
{
    pid_t pid = fork();

    if(pid == -1) 
    {
        perror("fork failed");
        return 1;
    }

    if(pid == 0) 
    {
        printf("Child: Before becoming orphan, PPID = %d\n", getppid());
        sleep(2);
        printf("Child: After becoming orphan, PPID = %d\n", getppid());
    } 
    else 
    {

        printf("Parent: PID = %d, exiting immediately!\n", getpid());
        exit(0);
    }

    return 0;
}

/*
==================================================
Output:
__________________________________________________
rohit2026~$gcc 24.c
rohit2026~$./a.out 
Parent: PID = 3489, exiting immediately!
Child: Before becoming orphan, PPID = 3489
rohit2026~$Child: After becoming orphan, PPID = 1
===============================================
*/
