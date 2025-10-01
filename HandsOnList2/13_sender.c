
/*
=====================================================================================
Name        : 13_sender.c
Author      : Rohitangshu Bose
Description : Write program to send the signal (using kill system call)
Date        : 1st October, 2025.
=====================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    int pid;
    printf("Enter pid of process to send SIGSTOP signal\n");
    scanf("%d", &pid);

    printf("SIGSTOP signal sent to process: %d\n", pid);
    kill(pid, SIGUSR1);

    printf("Exiting SIGSTOP signal sender process\n");
    return 0;
}
/*
================================================
Output:
________________________________________________
rohit2026~$gcc 13_sender.c -o sender.out
rohit2026~$./sender.out                 
Enter pid of process to send SIGSTOP signal
2548
SIGSTOP signal sent to process: 2548
Exiting SIGSTOP signal sender process
================================================
*/