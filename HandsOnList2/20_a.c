/*
===============================================================================
Name        : 20_a.c
Author      : Rohitangshu Bose
Description : Write two programs so that both can communicate by FIFO -Use one 
              way communication.(Write)
Date        : 29th September, 2025
===============================================================================
*/

#include<stdio.h>   
#include<unistd.h>   
#include<stdlib.h>    
#include<sys/stat.h>  
#include<sys/types.h>
#include<errno.h>  
#include<fcntl.h>
#include<string.h>

#define BUFFER_SIZE 256

int main() {
    if(mkfifo("myfifo",0777) == -1){
        if(errno != EEXIST){
            printf("FIFO file creation failed!!");
            return 1;
        }
    }
    printf("Opening FIFO......\n");
    int fd = open("myfifo",O_WRONLY);
    printf("FIFO opened......\n");
    char writeBuffer[BUFFER_SIZE];
    printf("Input a message to write to FIFO: ");
    scanf("%[^\n]",writeBuffer);
    if(write(fd,writeBuffer,strlen(writeBuffer)) == -1){
        perror("write failed");
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 20_a.c                                               
rohit2026~$gcc 20_a.c -o fifoWrite.out                              
rohit2026~$./fifoWrite.out 
Opening FIFO......
FIFO opened......
Input a message to write to FIFO: Hello there!!
================================================
*/