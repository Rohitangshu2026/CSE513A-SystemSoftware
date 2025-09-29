/*
==================================================================================
Name        : 18.c
Author      : Rohitangshu Bose
Description : Write a program to find out total number of directories on the pwd.
              execute ls -l | grep ^d | wc ? Use only dup2.
Date        : 29th September, 2025
==================================================================================
*/

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    int fd_p1[2];
    int fd_p2[2];

    if(pipe(fd_p1) == -1){
        printf("Error in opening pipe1");
        return 1;
    }
    if(pipe(fd_p2) == -1){
        printf("Error in opening pipe2");
        return 1;
    }

    int pid1 = fork();
    if(pid1 == -1){ 
        perror("fork failed");
        return 1;
    }

    else if(pid1 == 0){
        dup2(fd_p1[1],1);
        close(fd_p1[0]);
        close(fd_p1[1]);
        close(fd_p2[0]);
        close(fd_p2[1]);
        execlp("ls","ls","-l",(char*)NULL);
        perror("execlp failed");
        return 1;
    }

    else{
        int pid2 = fork();
        if(pid2 == -1){
            perror("fork failed");
            return 1;
        }
        else if(pid2 == 0){
            close(fd_p1[1]);
            close(fd_p2[0]);
            dup2(fd_p1[0], 0); 
            dup2(fd_p2[1], 1);
            close(fd_p1[0]);
            close(fd_p2[1]);
            execlp("grep", "grep", "^d", NULL);
        }
        else
        {
            close(fd_p2[1]);
            close(fd_p1[0]);
            close(fd_p1[1]);
            dup2(fd_p2[0], 0); 
            close(fd_p2[0]);
            execlp("wc", "wc", "-l", NULL);
        }

    }
    return 0;
}

/*
===================================================================
Output:
___________________________________________________________________
rohit2026~$gcc 18.c
rohit2026~$./a.out 
       0
rohit2026~$mkdir test
rohit2026~$gcc 18.c  
rohit2026~$./a.out   
       1
====================================================================
*/