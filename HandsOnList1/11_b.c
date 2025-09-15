/*
============================================================================
Name        : 11_b.c
Author      : Rohitangshu Bose
Description : Write a program to open a file, duplicate the file descriptor 
              and append the file with both the descriptors and check whether 
              the file is updated properly or not.
			  Use dup2
Date        : 7th September, 2025
============================================================================
*/

#include <unistd.h>    
#include <sys/types.h> 
#include <sys/stat.h>  
#include <fcntl.h>     
#include <stdio.h>     

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        printf("Requires file name as arguement\nUsage: %s <filename>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_WRONLY | O_APPEND);
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    int fd_copy = 10;
    if (dup2(fd, fd_copy) == -1) {
        perror("Failed to duplicate file descriptor using dup2");
        close(fd);
        return 1;
    }

    if (write(fd, "FIRSTWRITE", 10) != 10) 
    {
        perror("Failed writing to original descriptor");
        close(fd);
        close(fd_copy);
        return 1;
    }

    if (write(fd_copy, "SECONDWRITE", 11) != 11) 
    {
        perror("Failed writing to dup2 descriptor");
        close(fd);
        close(fd_copy);
        return 1;
    }

    printf("Data appended successfully using both descriptors (dup2).\n");

    close(fd);
    close(fd_copy);

    return 0;
}


/*
================================================================================
Output:
________________________________________________________________________________
rohit2026~$gcc 11_b.c      
rohit2026~$./a.out text.txt
Data appended successfully using both descriptors (dup2).
rohit2026~$cat text.txt    
FIRSTWRITESECONDWRITEFIRSTWRITESECONDWRITE% 
================================================================================
*/