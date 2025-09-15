/*
==============================================================================================
Name        : 16_a.c
Author      : Rohitangshu Bose
Description : Write a program to perform mandatory locking (implement readlock)
Date        : 7th September, 2025
==============================================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct flock lock;
    const char *filename = argv[1];

    int fd = open(filename, O_RDWR);
    if(fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    lock.l_type   = F_RDLCK; 
    lock.l_whence = SEEK_SET;  
    lock.l_start  = 0;       
    lock.l_len    = 0;        
    lock.l_pid    = getpid();  

    if(fcntl(fd, F_GETLK, &lock) == -1){
        perror("Error checking lock");
        close(fd);
        return 1;
    }

    if(lock.l_type == F_WRLCK)
    {
        printf("File has a write lock by PID %d\n", lock.l_pid);
    }
    else if(lock.l_type == F_RDLCK)
    {
        printf("File already has a read lock by PID %d\n", lock.l_pid);
    } 
    else 
    {
        if(fcntl(fd, F_SETLK, &lock) == -1)
        {
            perror("Error applying read lock");
        } 
        else 
        {
            printf("Read lock applied successfully\n");
        }
    }

    printf("Press Enter to release the lock...\n");
    getchar();

    lock.l_type = F_UNLCK;
    if(fcntl(fd, F_SETLK, &lock) == -1)
    {
        perror("Error releasing lock");
    } 
    else 
    {
        printf("Lock released\n");
    }

    close(fd);
    return 0;
}


/*
================================================================================
Output:
________________________________________________________________________________
rohit2026~$gcc 16_a.c      
rohit2026~$./a.out text.txt
Read lock applied successfully
Press Enter to release the lock...

Lock released                                                 
================================================================================
*/