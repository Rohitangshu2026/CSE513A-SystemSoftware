/*
======================================================================
Name : 01_b.c
Author : Rohitangshu Bose
Description : Create a hard link file using the link system call
Date: 1st September, 2025.
======================================================================
*/


#include <unistd.h> 
#include <stdio.h>  

int main(int argc, char *argv[]) 
{
    if (argc != 3) 
    {
        printf("Enter filenames\nUsage: %s <existing_file> <hard_link_name>\n", argv[0]);
        return 1;
    }

    const char *originalFile = argv[1];
    const char *hardLinkName = argv[2];

    if (link(originalFile, hardLinkName) == -1) {
        perror("Failed to create hard link");
        return 1;
    }

    printf("Hard link '%s' -> '%s' created successfully.\n", hardLinkName, originalFile);
    return 0;
}


/*
===============================================
Output:
_______________________________________________
rohit2026~$./a.out newFile.txt test.txt 
Hard link 'test.txt' -> 'newFile.txt' created successfully.
===============================================
*/
