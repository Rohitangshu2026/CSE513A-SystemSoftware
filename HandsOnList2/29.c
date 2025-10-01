/*
============================================================================
Name        : 29.c
Author      : Rohitangshu Bose
Description : Write a program to remove the message queue.
Date        : 30th September, 2025.
============================================================================
*/

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    key_t key = ftok(".", 'a');
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    int msqid = msgget(key, 0);
    if (msqid == -1) {
        perror("msgget failed");
        printf("Message queue doesnot exist!!\n");
        exit(1);
    }

    if(msgctl(msqid, IPC_RMID, NULL) == -1){
        printf("Deletion unsuccessful\n");
        exit(1);
    }
    else
        printf("Deleted successfully\n");
    return (0);
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 29.c
rohit2026~$./a.out 
Deleted successfully
rohit2026~$./a.out
msgget failed: No such file or directory
Message queue doesnot exist!!
================================================
*/