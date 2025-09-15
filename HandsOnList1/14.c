/*
============================================================================
Name        : 14.c
Author      : Rohitangshu Bose
Description : Write a pogram to find the type of a file.
              a. Input should be taken from command line.
              b. program should be able to identify any type of a file. 
Date        : 7th September, 2025
============================================================================
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        printf("Enter filename in arguement\nUsage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat file_info;

    if (lstat(argv[1], &file_info) == -1) 
    {
        perror("Error retrieving file info");
        return 1;
    }

    if (S_ISREG(file_info.st_mode)) printf("Regular File\n"); 
    else if (S_ISDIR(file_info.st_mode)) printf("Directory\n");
    else if (S_ISCHR(file_info.st_mode)) printf("Character Device\n");
    else if (S_ISBLK(file_info.st_mode)) printf("Block Device\n");
    else if (S_ISFIFO(file_info.st_mode)) printf("FIFO (Named Pipe)\n");
    else if (S_ISLNK(file_info.st_mode)) printf("Symbolic Link\n");
    else if (S_ISSOCK(file_info.st_mode)) printf("Socket\n");
    else printf("Unknown file type\n");

    return 0;
}

/*
================================================================================
Output:
________________________________________________________________________________
rohit2026~$gcc 14.c
rohit2026~$./a.out 
Enter filename in arguement
Usage: ./a.out <filename>
rohit2026~$./a.out 14.c
Regular File                                                        
================================================================================
*/