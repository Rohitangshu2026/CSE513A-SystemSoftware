/*
================================================================================================
Name        : 12.c
Author      : Rohitangshu Bose
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL 
              signal to the parent process from the child process.
Date        : 1st October, 2025.
=================================================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
#include<stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("CHILD : Child created with pid %d and parent's pid : %d.\n", getpid(), getppid());
        
        sleep(2);

        printf("CHILD : Sent SIGKILL to parent (%d).\n", getppid());
        
        if (kill(getppid(), SIGKILL) == -1) {
            perror("kill");
        }

        printf("CHILD : Parent should be terminated now.\n");
        
        sleep(3);
        

        printf("CHILD : Child's pid %d and parent's pid : %d.\n", getpid(), getppid());
        printf("CHILD: Exiting now.\n");
        
    } else {
        printf("PARENT : Parent process pid : %d and child's pid : %d.\n", getpid(), pid);
        
        printf("PARENT : Waiting to get terminated by child!!\n");
        sleep(10); 
        
        printf("PARENT : Survived!!\n");
    }

    return 0;
}


/*
============================================================
Output:
____________________________________________________________
rohit2026~$gcc 12.c
rohit2026~$./a.out
PARENT : Parent process pid : 2276 and child's pid : 2277.
PARENT : Waiting to get terminated by child!!
CHILD : Child created with pid 2277 and parent's pid : 2276.
CHILD : Sent SIGKILL to parent (2276).
CHILD : Parent should be terminated now.
zsh: killed     ./a.out
rohit2026~$CHILD : Child's pid 2277 and parent's pid : 1.
CHILD: Exiting now.
============================================================
*/