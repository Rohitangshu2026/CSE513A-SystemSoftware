/*
==============================================================================================
Name        : 17_a.c
Author      : Rohitangshu Bose
Description : 17. Write a program to simulate online ticket reservation. Implement write lock
                  Write a separate program, to open the file, implement write lock, 
                  read the ticket number, increment the number and print the new 
                  ticket number then close the file.
Date        : 7th September, 2025
==============================================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd;

    struct {
        int ticket_no;
    } db;


    fd = open("db", O_RDWR);
    if (fd == -1) {
        perror("Error opening ticket file");
        return 1;
    }


    struct flock lock;
    lock.l_type   = F_WRLCK;    
    lock.l_whence = SEEK_SET;
    lock.l_start  = 0;
    lock.l_len    = 0;         
    lock.l_pid    = getpid();

    printf("Before entering critical section\n");


    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error acquiring lock");
        close(fd);
        return 1;
    }

    printf("Inside critical section\n");


    lseek(fd, 0, SEEK_SET);
    if (read(fd, &db, sizeof(db)) == -1) {
        perror("Error reading file");
        close(fd);
        return 1;
    }

    printf("Current ticket number: %d\n", db.ticket_no);


    db.ticket_no++;


    lseek(fd, 0, SEEK_SET);
    if (write(fd, &db, sizeof(db)) == -1) {
        perror("Error writing file");
        close(fd);
        return 1;
    }

    printf("New ticket number: %d\n", db.ticket_no);

    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Error releasing lock");
    }

    printf("Exited critical section\n");

    close(fd);
    return 0;
}


/*
================================================================================
Output:
________________________________________________________________________________
rohit2026~$gcc 17_b.c
rohit2026~$./a.out   
Before entering critical section
Inside critical section
Current ticket number: 10
New ticket number: 11
Exited critical section                                        
================================================================================
*/


