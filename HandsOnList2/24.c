/*
============================================================
Name        : 24.c
Author      : Rohitangshu Bose
Description : Write a program to create a message queue and 
              print the key and message queue id.
Date        : 30th September, 2025.
============================================================
*/

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
int main()
{
    key_t key = ftok(".", 'a');
    int msqid = msgget(key, IPC_CREAT | 0666);
    printf("Key: %d\nMessage Queue ID: %d\n", key, msqid);
    return(0);
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 24.c
rohit2026~$./a.out 
Key: 1628439487
Message Queue ID: 65536
================================================
*/