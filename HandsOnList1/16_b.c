/*
==============================================================================================
Name        : 16_b.c
Author      : Rohitangshu Bose
Description : Write a program to perform mandatory locking (implement write lock)
Date        : 7th September, 2025
==============================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
    
int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        printf("Enter filename as arguement\nUsage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    struct flock lock;
    int fd;

    fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    lock.l_type   = F_WRLCK;    
    lock.l_whence = SEEK_SET;  
    lock.l_start  = 0;          
    lock.l_len    = 0;          
    lock.l_pid    = getpid();  

    printf("Before entering critical section\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Failed to acquire lock");
        close(fd);
        return 1;
    }

    printf("Inside the critical section\n");
    printf("Press Enter to unlock the file...\n");

    getchar();

    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Failed to release lock");
    }

    printf("File unlocked\n");
    printf("End of program\n");

    close(fd);
    return 0;
}

/*
================================================================================
Output:
________________________________________________________________________________
rohit2026~$./a.out text.txt                                     
Before entering critical section
Inside the critical section
Press Enter to unlock the file...

File unlocked
End of program                                                   
================================================================================
*/