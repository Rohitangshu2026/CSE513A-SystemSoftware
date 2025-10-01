/*
======================================================================================
Name        : 32_a.c
Author      : Rohitangshu Bose
Description : Write a program to implement semaphore to protect any critical section.
                a. rewrite the ticket number creation program using semaphore
Date        : 30th September, 2025.
======================================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/sem.h>

struct ticket
{
    int train;
    int tickets;
};



int main()
{

    int fd = open("TicketRecord.txt", O_RDWR | O_CREAT, 0744);
    struct ticket ticket1 = {513,0};

    write(fd, &ticket1, sizeof(struct ticket));

    printf("Train name: %d\n", ticket1.train);
    printf("Ticket number: %d\n", ticket1.tickets);

    close(fd);

    int key = ftok(".", 'a');
    int sem_id = semget(key, 1, IPC_CREAT | 0666);

    union semun arg;
    arg.val = 1;
    semctl(sem_id, 0, SETVAL, arg);

    return 0;
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 32_a.c
rohit2026~$./a.out   
Train name: 513
Ticket number: 0
================================================
*/