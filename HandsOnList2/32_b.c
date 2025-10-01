/*
=====================================================================================
Name        : 32_b.c
Author      : Rohitangshu Bose
Description : Write a program to implement semaphore to protect any critical section.
                b. protect shared memory from concurrent write access
Date        : 30th September, 2025.
=====================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/sem.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

struct ticket
{
    int train;
    int tickets;
};

struct sembuf op;

int main()
{

    int fd = open("TicketRecord.txt", O_RDWR);

    if (fd == -1)
    {
        printf("open failed\n");
        return -1;
    }

    int key = ftok(".", 'a');
    int sem_id = semget(key, 1, 0);

    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = 0;

    printf("Locking\n");
    int ret = semop(sem_id, &op, 1);

    if (ret == -1)
    {
        printf("semaphore failed\n");
        return -1;
    }

    printf("Locked\n");

    struct ticket ticket1;
    read(fd, &ticket1, sizeof(struct ticket));

    printf("Current ticket number: %d\n", ticket1.tickets);

    ticket1.tickets += 1;
    lseek(fd, 0, SEEK_SET);
    write(fd, &ticket1, sizeof(struct ticket));

    lseek(fd, 0, SEEK_SET); 
    read(fd, &ticket1, sizeof(struct ticket));

    printf("Incremented ticket number: %d\n", ticket1.tickets);

    printf("Press enter to unlock\n");
    char ch;
    scanf("%c", &ch);

    while (ch != '\n')
        scanf(" %c", &ch);

    op.sem_op = 1;
    ret = semop(sem_id, &op, 1); // unlocking

    printf("Semaphore unlocked\n");

    close(fd);
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 32_b.c
rohit2026~$./a.out   
Locking
Locked
Current ticket number: 0
Incremented ticket number: 1
Press enter to unlock

Semaphore unlocked
rohit2026~$./a.out
Locking
Locked
Current ticket number: 2
Incremented ticket number: 3
Press enter to unlock

Semaphore unlocked
================================================
*/