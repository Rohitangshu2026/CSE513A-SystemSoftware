/*
===============================================================================
Name        : 20_b.c
Author      : Rohitangshu Bose
Description : Write two programs so that both can communicate by FIFO -Use one 
              way communication.(Read)
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
    int fd = open("myfifo",O_RDONLY);
    printf("FIFO opened......\n");
    char readBuffer[BUFFER_SIZE];
    ssize_t bytesRead = read(fd,readBuffer,sizeof(readBuffer) - 1);
    if(bytesRead == -1){
        perror("read failed");
        close(fd);
        return 1;
    }
    readBuffer[bytesRead] = '\0';
    printf("Read from FIFO: %s\n",readBuffer);
    close(fd);
    return 0;
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 20_b.c -o fifoRead.out
rohit2026~$./fifoRead.out            
Opening FIFO......
FIFO opened......
Read from FIFO: Hello there!!
================================================
*/