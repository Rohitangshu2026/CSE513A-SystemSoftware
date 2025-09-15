/*
============================================================================
Name        : 01_c_new.c
Author      : Rohitangshu Bose
Description : Create FIFO (named pipe) files using `mkfifo` and `mknod`
Date        : 07th Sep, 2025
============================================================================
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 3) 
    {
        printf("Usage: %s <mkfifo_file> <mknod_fifo_file>\n", argv[0]);
        return 1;
    }

    const char *fifo_mkfifo = argv[1];
    const char *fifo_mknod = argv[2];

    if (mkfifo(fifo_mkfifo, S_IRWXU) == -1) 
    {
        perror("Failed to create FIFO with mkfifo");
    } 
    else 
    {
        printf("FIFO created successfully using mkfifo: %s\n", fifo_mkfifo);
    }

    if (mknod(fifo_mknod, S_IFIFO | S_IRWXU, 0) == -1) 
    {
        perror("Failed to create FIFO with mknod");
    } 
    else 
    {
        printf("FIFO created successfully using mknod: %s\n", fifo_mknod);
    }

    return 0;
}

/*
===============================================
Output:
_______________________________________________
rohit2026~$./a.out mkfifo mknod
FIFO created successfully using mkfifo: mkfifo
FIFO created successfully using mknod: mknod
===============================================
*/