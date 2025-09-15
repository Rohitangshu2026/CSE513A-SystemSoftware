/*
============================================================================
Name        : 09.c
Author      : Rohitangshu Bose
Description : Write a program to print the following information about a given file - 
                a. Inode 
                b. Number of hard links 
                c. UID 
                d. GID 
                e. Size 
                f. Block size 
                g. Number of blocks 
                h. Time of last access 
                h. Time of last modification 
                i. Time of last change
Date        : 1st September,2025
============================================================================
*/

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        printf("Requires file name as arguement\nUsage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat fileStat;
    if (stat(argv[1], &fileStat) != 0) 
    {
        perror("Failed to retrieve file information");
        return 1;
    }

    printf("File: %s\n", argv[1]);
    printf("Inode number: %llu\n", (unsigned long long)fileStat.st_ino);
    printf("Hard links: %lu\n", (unsigned long)fileStat.st_nlink);
    printf("Owner UID: %u\n", fileStat.st_uid);
    printf("Group GID: %u\n", fileStat.st_gid);
    printf("File size: %lld bytes\n", (long long)fileStat.st_size);
    printf("Preferred block size: %ld bytes\n", (long)fileStat.st_blksize);
    printf("Number of blocks allocated: %lld\n", (long long)fileStat.st_blocks);
    printf("Last access time: %s", ctime(&fileStat.st_atime));
    printf("Last modification time: %s", ctime(&fileStat.st_mtime));
    printf("Last status change: %s", ctime(&fileStat.st_ctime));

    return 0;
}

/*
================================================================================
Output:
________________________________________________________________________________
rohit2026~$gcc 09.c        
rohit2026~$./a.out         
Requires file name as arguement
Usage: ./a.out <filename>
rohit2026~$./a.out 09.c
File: 09.c
Inode number: 3109569
Hard links: 1
Owner UID: 501
Group GID: 20
File size: 2056 bytes
Preferred block size: 4096 bytes
Number of blocks allocated: 8
Last access time: Sun Sep  7 20:05:13 2025
Last modification time: Sun Sep  7 20:05:12 2025
Last status change: Sun Sep  7 20:05:12 2025
================================================================================
*/
