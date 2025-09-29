/*
============================================================================
Name        : 17_b.c
Author      : Rohitangshu Bose
Description : 17. Write a program to execute ls -l | wc.
                b. use dup2
Date        : 29th September, 2025
============================================================================
*/

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    int fd[2];
    if(pipe(fd) == -1){
        printf("Error in opening pipe");
        return 1;
    }

    int pid = fork();
    if(pid == -1){
        perror("fork failed");
        return 1;
    }

    else if(pid == 0){
        close(fd[0]);
        dup2(fd[1],1);
        close(fd[1]);
        execlp("ls","ls","-l",(char*)NULL);
        perror("execlp failed");
        return 1;
    }

    else{
        close(fd[1]);
        dup2(fd[0],0);
        close(fd[0]);
        execlp("wc","wc",(char*)NULL);
        perror("execlp failed");
        return 1;
    }

    return 0;
}

/*
===================================================================
Output:
___________________________________________________________________
rohit2026~$gcc 17_b.c
rohit2026~$./a.out   
      12     103     658
====================================================================
*/