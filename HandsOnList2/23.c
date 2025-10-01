/*
============================================================================
Name        : 23.c
Author      : Rohitangshu bose
Description : Write a program to print the maximum number of files can be 
              opened within a process and size of a pipe (circular buffer).
Date        : 30th September, 2025.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>

int main(){
    long pipeSize, maxOpen;
    
    pipeSize = pathconf(".", _PC_PIPE_BUF);
    maxOpen = sysconf(_SC_OPEN_MAX);

    printf("Maximum open files = %ld\nPipe Size = %ld\n", maxOpen, pipeSize);
    
    return(0);
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 23.c
rohit2026~$./a.out 
Maximum open files = 256
Pipe Size = 512
================================================
*/