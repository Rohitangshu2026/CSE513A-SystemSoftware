/*
==============================================================================================
Name        : 17_a.c
Author      : Rohitangshu Bose
Description : 17. Write a program to simulate online ticket reservation. Implement write lock
                  Write a program to open a file, store a ticket number and exit. 
Date        : 7th September, 2025
==============================================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() 
{
    int fd;

    struct 
    {
        int ticket_no;
    } db;

    db.ticket_no = 10;


    fd = open("db", O_CREAT | O_RDWR, 0744);
    if (fd == -1) {
        perror("Error opening/creating file");
        return 1;
    }

    if (write(fd, &db, sizeof(db)) == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    close(fd);


    fd = open("db", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for read");
        return 1;
    }

    if (read(fd, &db, sizeof(db)) == -1) {
        perror("Error reading from file");
        close(fd);
        return 1;
    }

    printf("Ticket no: %d\n", db.ticket_no);
    close(fd);

    return 0;
}

/*
================================================================================
Output:
________________________________________________________________________________
rohit2026~$gcc 17_a.c
rohit2026~$./a.out
Ticket no: 10                                             
================================================================================
*/

