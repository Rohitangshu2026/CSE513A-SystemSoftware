/*
============================================================================
Name        : 17_c.c
Author      : Rohitangshu Bose
Description : 17. Write a program to execute ls -l | wc.
                c. use fcntl
Date        : 29th September, 2025
============================================================================
*/

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

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
        close(1);
        close(fd[0]);
        if(fcntl(fd[1],F_DUPFD,1) == -1){
            perror("fcntl failed");
            return 1;
        }
        close(fd[1]);
        execlp("ls","ls","-l",(char*)NULL);
        perror("execlp failed");
        return 1;
    }
    
    else{
        close(0);
        close(fd[1]);
        if(fcntl(fd[0],F_DUPFD,0) == -1){
            perror("fcntl failed");
            return 1;
        }
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
rohit2026~$gcc 17_a.c
rohit2026~$./a.out
      13     112     717
====================================================================
*/