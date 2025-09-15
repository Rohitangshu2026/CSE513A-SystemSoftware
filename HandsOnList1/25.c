/*
==============================================================
Name        : 25.c
Author      : Rohitangshu Bose
Description : Write a program to create three child processes. 
              The parent should wait for a particular child 
              (use waitpid system call)
Date        : 1st September, 2025
==============================================================
*/

#include <unistd.h>    
#include <sys/types.h> 
#include <sys/wait.h>  
#include <stdio.h>     

int main() 
{
    pid_t childA, childB, childC;
    pid_t awaitedChild;
    int waitStatus;

    childA = fork();
    if (childA == -1) 
    {
        perror("Error creating Child A");
        return 1;
    }
    if (childA == 0) 
    { 
        printf("Child A created! PID: %d\n", getpid());
        printf("Child A put to sleep for 2s! %d\n", getpid());
        sleep(2);
        printf("Child A exits!\n");
        _exit(0);
    }

    childB = fork();
    if (childB == -1) 
    {
        perror("Error creating Child B");
        return 1;
    }
    if (childB == 0) 
    {
        printf("Child B created! PID: %d\n", getpid());
        printf("Child A put to sleep for 4s! %d\n", getpid());
        sleep(4);
        printf("Child B exits!\n");
        _exit(0);
    }

    // Create Child C
    childC = fork();
    if (childC == -1) 
    {
        perror("Error creating Child C");
        return 1;
    }
    if (childC == 0) 
    { 
        printf("Child C created! PID: %d\n", getpid());
        printf("Child A put to sleep for 8s! %d\n", getpid());
        sleep(8);
        printf("Child C exits!\n");
        _exit(0);
    }

    printf("Parent waiting for Child C (PID: %d)...\n", childC);
    awaitedChild = waitpid(childC, &waitStatus, 0);
    if (awaitedChild == childC) 
        printf("Child C exited with status: %d\n", waitStatus);
    else
        perror("Error waiting for Child C");

    return 0;
}
/*
==================================================
Output:
__________________________________________________
rohit2026~$gcc 25.c
rohit2026~$./a.out 
Child A created! PID: 3574
Child A put to sleep for 2s! 3574
Child B created! PID: 3575
Parent waiting for Child C (PID: 3576)...
Child A put to sleep for 4s! 3575
Child C created! PID: 3576
Child A put to sleep for 8s! 3576
Child A exits!
Child B exits!
Child C exits!
Child C exited with status: 0
=================================================
*/