/*
======================================================================================
Name        : 30_b.c
Author      : Rohitangshu Bose
Description : Write a program to create a shared memory.
                b. attach with O_RDONLY and check whether you are able to overwrite.
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
    printf("Shared memory segment ID: %d\n", shmid);

    data = (char *)shmat(shmid, NULL, SHM_RDONLY);
    if (data == (void *)-1) {
        perror("shmat read-mode failed");
        exit(1);
    }

    printf("Data in shared memory (read-only): %s\n", data);



    printf("Enter text to overwrite in shared memory: ");
    scanf("%[^\n]s", data);
    printf("Write to shared memory sucessful!!\n");


    if(shmdt(data) == -1) {
        perror("shmdt failed");
        exit(1);
    }

    return 0;
}
/*
===============================================================
Output:
_______________________________________________________________
rohit2026~$gcc 30_b.c
rohit2026~$./a.out
Shared memory segment ID: 65536
Data in shared memory (read-only): Writing to shared memory!!!
Enter text to overwrite in shared memory: Hi
zsh: bus error  ./a.out
===============================================================
*/