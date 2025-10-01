/*
============================================================================
Name        : 28.c
Author      : Rohitangshu Bose
Description : Write a program to change the exiting message queue 
              permission. (Use msqid_ds structure)
Date        : 30th September, 2025.
============================================================================
*/

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>

int main() {
    key_t key = ftok(".", 'a');

    int msqid = msgget(key, IPC_CREAT | IPC_EXCL | 0666);
    if (msqid == -1) {
        perror("msgget");
        msqid = msgget(key, 0);
    }
    
    struct msqid_ds queue_info;

    if (msgctl(msqid, IPC_STAT, &queue_info) == -1) {
        perror("msgctl IPC_STAT");
        exit(1);
    }
    printf("Current access Permissions: %o\n", queue_info.msg_perm.mode);

    queue_info.msg_perm.mode = 0777;

    if (msgctl(msqid, IPC_SET, &queue_info) == -1) {
        perror("msgctl IPC_SET");
        exit(1);
    }

    if (msgctl(msqid, IPC_STAT, &queue_info) == -1) {
        perror("msgctl IPC_STAT verification");
        exit(1);
    }
    printf("New access Permissions: %o\n", queue_info.msg_perm.mode);

    msgctl(msqid, IPC_RMID, NULL);

    return 0;
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 28.c
rohit2026~$./a.out 
msgget: File exists
Current access Permissions: 666
New access Permissions: 777
================================================
*/