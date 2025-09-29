/*
===============================================================================
Name        : 21_b.c
Author      : Rohitangshu Bose
Description : Write two programs so that both can communicate by FIFO -Use two
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
    if(mkfifo("myfifo1",0777) == -1){
        if(errno != EEXIST){
            printf("FIFO file creation failed!!");
            return 1;
        }
    }
    if(mkfifo("myfifo2",0777) == -1){
        if(errno != EEXIST){
            printf("FIFO file creation failed!!");
            return 1;
        }
    }
    printf("Opening FIFO......\n");
    int fd1 = open("myfifo1",O_RDONLY);
    int fd2 = open("myfifo2",O_WRONLY);
    printf("FIFO opened......\n");
    char readBuffer[BUFFER_SIZE];
    ssize_t bytesRead = read(fd1,readBuffer,sizeof(readBuffer) - 1);
    if(bytesRead == -1){
        perror("read failed");
        close(fd1);
        return 1;
    }
    readBuffer[bytesRead] = '\0';
    printf("Read from FIFO: %s\n",readBuffer);
    close(fd1);
    char writeBuffer[BUFFER_SIZE];
    printf("Input a message to write to FIFO: ");
    scanf("%[^\n]",writeBuffer);
    if(write(fd2,writeBuffer,strlen(writeBuffer)) == -1){
        perror("write failed");
        close(fd2);
        return 1;
    }
    close(fd2);
    return 0;
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 21_b.c -o fifo2.out
rohit2026~$./fifo2.out            
Opening FIFO......
FIFO opened......
Read from FIFO: hello
Input a message to write to FIFO: hi!!
================================================
*/