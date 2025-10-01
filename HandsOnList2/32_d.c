/*
======================================================================================
Name        : 32_d.c
Author      : Rohitangshu Bose
Description : Write a program to implement semaphore to protect any critical section.
                d. remove the created semaphore
Date        : 1st October, 2025.
======================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/types.h>

int main()
{
    key_t key = ftok(".", 'a');
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    int sem_id = semget(key, 1, 0);
    if (sem_id == -1) {
        perror("semget");
        return 1;
    }

    printf("Removing semaphore with ID: %d\n", sem_id);

    if (semctl(sem_id, 0, IPC_RMID) == -1) {
        perror("semctl");
        printf("Semaphore removal unsuccessful.\n");
        return 1;
    }

    printf("Semaphore removed successfully.\n");
    
    return 0;
}