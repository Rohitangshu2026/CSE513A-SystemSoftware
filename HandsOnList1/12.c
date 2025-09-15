/*
============================================================================
Name        : 12.c
Author      : Rohitangshu Bose
Description : Write a program to find out the opening mode of a file. Use fcntl.
Date        : 1st September, 2025
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        printf("Enter file name in arguement\nUsage: %s <filename>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd == -1) 
    {
        perror("Failed to open file");
        return 1;
    }

    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) 
    {
        perror("fcntl failed");
        close(fd);
        return 1;
    }

    int accessMode = flags & O_ACCMODE;
    printf("File: %s\n", argv[1]);
    printf("Access mode: ");
    switch (accessMode) 
    {
        case O_RDONLY: printf("Read Only\n"); break;
        case O_WRONLY: printf("Write Only\n"); break;
        case O_RDWR:   printf("Read/Write\n"); break;
        default:       printf("Unknown\n");
    }

    if (flags & O_APPEND)   printf("O_APPEND is set\n");
    if (flags & O_CREAT)    printf("O_CREAT is set\n");
    if (flags & O_TRUNC)    printf("O_TRUNC is set\n");
    if (flags & O_NONBLOCK) printf("O_NONBLOCK is set\n");
    if (flags & O_SYNC)     printf("O_SYNC is set\n");

    close(fd);
    return 0;
}

/*
================================================================================
Output:
________________________________________________________________________________
rohit2026~$gcc 12.c        
rohit2026~$./a.out text.txt
File: text.txt
Access mode: Read/Write
rohit2026~$./a.out 12.c    
File: 12.c
Access mode: Read/Write
rohit2026~$                                                            
================================================================================
*/