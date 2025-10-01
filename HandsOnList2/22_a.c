/*
===============================================================================
Name        : 22_a.c
Author      : Rohitangshu Bose
Description : Write a program to wait for data to be written into FIFO within 10 
              seconds, use select system call with FIFO.(Write)
Date        : 30th September, 2025
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
rohit2026~$gcc 22_a.c -o fifoWrite.out
rohit2026~$./fifoWrite.out 
Opening FIFO......
FIFO opened......
Input a message to write to FIFO: Hello
rohit2026~$./fifoWrite.out            
Opening FIFO......
FIFO opened......
Input a message to write to FIFO:
================================================
*/