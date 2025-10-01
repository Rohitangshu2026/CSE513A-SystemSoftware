/*
=====================================================================
Name        : 26.c
Author      : Rohitangshu Bose
Description : Write a program to send messages to the message queue. 
              Check $ipcs -q
Date        : 30th September, 2025.
=====================================================================
*/

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    struct msg {
    long int m_type;
    char message[80];
    } mq;
    key_t key = ftok(".", 'a');
    int mqid = msgget(key, 0);
    printf("Enter message type : ");
    scanf("%ld", &mq.m_type);
    while(getchar() != '\n');
    printf("Enter message text : ");
    scanf("%[^\n]", mq.message);
    if (msgsnd(mqid, &mq, strlen(mq.message) + 1, 0) == -1) {
        perror("msgsnd failed");
        exit(1);
    }

    printf("Message sent successfully to queue ID : %d\n", mqid);
    return(0);
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 26.c
rohit2026~$./a.out 
Enter message type : 1
Enter message text : Sending Message to queue!!
Message sent successfully to queue ID : 65536
rohit2026~$ipcs -q
IPC status from <running system> as of Tue Sep 30 10:02:00 IST 2025
T     ID     KEY        MODE       OWNER    GROUP
Message Queues:
q  65536 0x611003bf --rw-rw-rw- rohit2026    staff
================================================
*/