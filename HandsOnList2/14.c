/*
==========================================================================
Name        : 14.c
Author      : Rohitangshu Bose
Description : Write a simple program to create a pipe, write to the pipe, read 
              from pipe and display on the monitor.
Date        : 29th September, 2025
==========================================================================
*/

#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<string.h>

#define BUFFER_SIZE 256

int main(){
    int fd[2];
    if(pipe(fd) == -1){
        printf("Error in opening pipe!!\n");
        return 1;
    }
    char writeBuffer[BUFFER_SIZE];
    printf("Writing to pipe: ");
    scanf("%[^\n]",writeBuffer);
    if(write(fd[1],writeBuffer,strlen(writeBuffer)) == -1){
        perror("write failed");
        close(fd[1]);
        return 1;
    }
    close(fd[1]);
    char readBuffer[BUFFER_SIZE];
    ssize_t bytesRead = read(fd[0],readBuffer,sizeof(readBuffer) - 1);
    if(bytesRead == -1){
        perror("read failed");
        close(fd[0]);
        return 1;
    }
    readBuffer[bytesRead] = '\0';
    close(fd[0]);
    printf("Reading from pipe: %s\n",readBuffer);  
    return 0;
}

/*
===================================================================
Output:
___________________________________________________________________
rohit2026~$gcc 14.c
rohit2026~$./a.out 
Writing to pipe: Writing to pipe!!
Reading from pipe: Writing to pipe!!
====================================================================
*/