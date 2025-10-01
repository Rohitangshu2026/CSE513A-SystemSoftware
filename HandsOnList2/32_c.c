/*
======================================================================================
Name        : 32_c.c
Author      : Rohitangshu Bose
Description : Protect multiple pseudo resources (two) using a counting semaphore.
Date        : 1st October, 2025.
======================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define NUM_RESOURCES 2
#define NUM_PROCESSES 3



void use_resource(int process_num) {
    printf("Process %d has acquired a resource and is now working.\n", process_num);
    sleep(3);
    printf("Process %d is releasing the resource.\n", process_num);
}

int main() {
    key_t key;
    int semid;
    union semun sem_arg;

    key = ftok(".", 'r');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    sem_arg.val = NUM_RESOURCES;
    if (semctl(semid, 0, SETVAL, sem_arg) == -1) {
        perror("semctl SETVAL");
        exit(1);
    }
    printf("Counting semaphore created with %d available resources.\n\n", NUM_RESOURCES);

    struct sembuf sem_wait = {0, -1, SEM_UNDO};
    struct sembuf sem_signal = {0, 1, SEM_UNDO};

    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (fork() == 0) {
            printf("Process %d is attempting to acquire a resource...\n", i + 1);
            
            if (semop(semid, &sem_wait, 1) == -1) {
                perror("semop wait");
                exit(1);
            }
            
            use_resource(i + 1);

            if (semop(semid, &sem_signal, 1) == -1) {
                perror("semop signal");
                exit(1);
            }
            exit(0);
        }
    }

    for (int i = 0; i < NUM_PROCESSES; i++) {
        wait(NULL);
    }

    if (semctl(semid, 0, IPC_RMID, NULL) == -1) {
        perror("semctl IPC_RMID");
    }
    printf("\nAll processes finished!\nSemaphore has been removed.\n");

    return 0;
}
/*
===================================================================
Output:
___________________________________________________________________
rohit2026~$gcc 32_c.c
rohit2026~$./a.out
Counting semaphore created with 2 available resources.

Process 1 is attempting to acquire a resource...
Process 1 has acquired a resource and is now working.
Process 2 is attempting to acquire a resource...
Process 2 has acquired a resource and is now working.
Process 3 is attempting to acquire a resource...
Process 1 is releasing the resource.
Process 3 has acquired a resource and is now working.
Process 2 is releasing the resource.
Process 3 is releasing the resource.

All processes finished!
Semaphore has been removed.
====================================================================
*/
