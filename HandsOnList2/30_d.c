/*
======================================================================================
Name        : 30_d.c
Author      : Rohitangshu Bose
Description : Write a program to create a shared memory.
                d. remove the shared memory
Date        : 30th September, 2025.
======================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>

int main() {
    key_t key;
    int shmid;
    char *data;

    key = ftok(".", 's'); 
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    shmid = shmget(key, 1024, 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }
    printf("Shared memory segment with ID: %d\n", shmid);

    if (shmctl(shmid, IPC_RMID, NULL) == -1)
        printf("Deletion unsuccessful\n");
    else
        printf("Deleted successful\n");

    return 0;
}
/*
================================================
Output:
________________________________________________
rohit2026~$gcc 30_d.c
rohit2026~$./a.out
Shared memory segment with ID: 65536
Deleted successful
================================================
*/