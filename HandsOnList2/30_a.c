/*
======================================================================================
Name        : 30_a.c
Author      : Rohitangshu Bose
Description : Write a program to create a shared memory.
                a. write some data to the shared memory
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

    shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }
    printf("Shared memory segment created with ID: %d\n", shmid);

    data = shmat(shmid, 0, 0);
    if (data == (void *)-1) {
        perror("shmat write-mode failed");
        exit(1);
    }

    printf("Enter text to write in shared memory: ");
    scanf("%[^\n]s", data);
    printf("Write to shared memory sucessful!!\n");

    if (shmdt(data) == -1) {                        
        perror("shmdt failed");
        exit(1);
    }

    return 0;
}
/*
=================================================================
Output:
_________________________________________________________________
rohit2026~$gcc 30_a.c
rohit2026~$./a.out   
Shared memory segment created with ID: 65536
Enter text to write in shared memory: Writing to shared memory!!
Write to shared memory sucessful!!
=================================================================
*/