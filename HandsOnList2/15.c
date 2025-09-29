/*
==========================================================================
Name        : 15.c
Author      : Rohitangshu Bose
Description : Write a simple program to send some data from parent to 
              the child process.
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
    int id = fork();
    if(id == -1){
        perror("fork failed");
        return 1;
    }
    else if(id > 0){
        close(fd[0]);
        char writeBuffer[BUFFER_SIZE];
        printf("Input a message parent passes to child: ");
        scanf("%[^\n]",writeBuffer);
        if(write(fd[1],writeBuffer,strlen(writeBuffer)) == -1){
            perror("write failed");
            close(fd[1]);
            return 1;
        }
        close(fd[1]);
        wait(NULL);
    }
    else{
        close(fd[1]);
        char readBuffer[BUFFER_SIZE];
        ssize_t bytesRead = read(fd[0],readBuffer,sizeof(readBuffer) - 1);
        if(bytesRead == -1){
            perror("read failed");
            close(fd[0]);
            return 1;
        }
        readBuffer[bytesRead] = '\0';
        printf("Read from pipe by the child: %s\n",readBuffer);
        close(fd[0]);
    }
    return 0;
}

/*
===================================================================
Output:
___________________________________________________________________
rohit2026~$gcc 15.c
rohit2026~$./a.out 
Input a message parent passes to child: Using pipe to pass data!!
Read from pipe by the child: Using pipe to pass data!!
====================================================================
*/