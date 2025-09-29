/*
============================================================================
Name        : 16.c
Author      : Rohitangshu Bose
Description : Write a program to send and receive data from parent to child 
              vice versa. Use two way communication.
Date        : 29th September, 2025
============================================================================
*/

#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<string.h>

#define BUFFER_SIZE 256

int main(){
   int fd_p1[2];    //  Pipe1: Parent -> Child
   int fd_p2[2];    //  Pipe2: Child -> Parent

    if(pipe(fd_p1) == -1){
        printf("Error in opening pipe1");
        return 1;
    }
    if(pipe(fd_p2) == -1){
        printf("Error in opening pipe2");
        return 1;
    }

    int pid = fork();
    if(pid == -1){
        perror("fork failed");
        return 1;
    }

    else if(pid > 0){
        close(fd_p1[0]);
        close(fd_p2[1]);
        char parentWriteBuffer[BUFFER_SIZE];
        char parentReadBuffer[BUFFER_SIZE];

        printf("Parent: Input a message to pass to child: ");
        scanf("%[^\n]",parentWriteBuffer);
        if(write(fd_p1[1],parentWriteBuffer,strlen(parentWriteBuffer)) == -1){
            close(fd_p1[1]);
            close(fd_p2[0]);
            perror("Parent write failed");
            return 1;
        }

        ssize_t parentBytesRead = read(fd_p2[0],parentReadBuffer,sizeof(parentReadBuffer) - 1);
        if(parentBytesRead == -1){
            perror("Parent read failed");
            close(fd_p2[0]);
            close(fd_p1[1]);
            return 1;
        }
        parentReadBuffer[parentBytesRead] = '\0';
        printf("Parent: Message received from child: \"%s\"\n", parentReadBuffer);

        close(fd_p1[1]);
        close(fd_p2[0]);

        wait(NULL);
    }
    else if(pid == 0){
        close(fd_p1[1]);
        close(fd_p2[0]);

        char childReadBuffer[BUFFER_SIZE];

        ssize_t childBytesRead = read(fd_p1[0], childReadBuffer, sizeof(childReadBuffer) - 1);
        if (childBytesRead == -1) {
            perror("Child read failed");
            close(fd_p1[0]);
            close(fd_p2[1]);
            return 1;
        }
        childReadBuffer[childBytesRead] = '\0';
        printf("Child: Message received from parent: \"%s\"\n", childReadBuffer);
        
        printf("Child: Sending acknowledgment to parent!!\n");
        if(write(fd_p2[1], "Message received!!", 19 ) == -1) {
            perror("Child write failed");
            close(fd_p1[0]);
            close(fd_p2[1]);
            return 1;
        }

        close(fd_p1[0]);
        close(fd_p2[1]);
    }

    return 0;
}

/*
===================================================================
Output:
___________________________________________________________________
rohit2026~$gcc 16.c
rohit2026~$./a.out 
Parent: Input a message to pass to child: Two way pipe working?
Child: Message received from parent: "Two way pipe working?"
Child: Sending acknowledgment to parent!!
Parent: Message received from child: "Message received!!"
====================================================================
*/