/*
===============================================================================
Name        : 22_b.c
Author      : Rohitangshu Bose
Description : Write a program to wait for data to be written into FIFO within 10 
              seconds, use select system call with FIFO.(Read)
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
#include<sys/select.h>

#define BUFFER_SIZE 256

int main() {
    fd_set rfds;
    struct timeval tv;
    
    tv.tv_sec = 10;
    
    if(mkfifo("myfifo",0777) == -1){
        if(errno != EEXIST){
            printf("FIFO file creation failed!!");
            return 1;
        }
    }

    printf("Opening FIFO......\n");
    int fd = open("myfifo",O_RDONLY);
    printf("FIFO opened......\n");
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    if (!select(fd + 1, &rfds, NULL, NULL, &tv)) {
        printf("No data availabe!!\n");
    }
	
    else{

        char readBuffer[BUFFER_SIZE];
        ssize_t bytesRead = read(fd,readBuffer,sizeof(readBuffer) - 1);
        if(bytesRead == -1){
            perror("read failed");
            close(fd);
            return 1;
        }
        readBuffer[bytesRead] = '\0';
        printf("Read from FIFO: %s\n",readBuffer);
    }
    close(fd);
    return 0;
}
/*
================================================
Output:
________________________________________________
rohit2026~$gcc 22_b.c -o fifoRead.out
rohit2026~$./fifoRead.out 
Opening FIFO......
FIFO opened......
Read from FIFO: Hello
rohit2026~$./fifoRead.out
Opening FIFO......
FIFO opened......
No data availabe!!
================================================
*/