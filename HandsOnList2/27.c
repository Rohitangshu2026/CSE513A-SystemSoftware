/*
==========================================================================
Name        : 27.c
Author      : Rohitangshu Bose
Description : Write a program to receive messages from the message queue.
                a. with 0 as a flag
                b. with IPC_NOWAIT as a flag
Date        : 30th September, 2025.
==========================================================================
*/

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {
    struct msg {
        long int m_type;
        char message[80];
    } mq;
    int choice;
    int flags = 0;
    key_t key = ftok(".", 'a');
    int mqid = msgget(key, 0);
    printf("Enter message type: ");
    scanf("%ld", &mq.m_type);

    printf("Choose  flag for msgrcv:\n");
    printf("1. 0 (Wait/Block until a message arrives)\n");
    printf("2. IPC_NOWAIT (Return immediately if no message is present)\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    if (choice == 2) {
        flags = IPC_NOWAIT;
        printf("Using IPC_NOWAIT flag. The program will not wait.\n");
    } 
    else {
        printf("Using 0 as the flag. The program will wait for a message...\n");
    }

    int ret = msgrcv(mqid, &mq, sizeof(mq.message), mq.m_type, flags | MSG_NOERROR);
    if (ret == -1){
        exit(-1);
        perror("msgrcv failed");
    }

    printf("Message received successfully!\n");
    printf("Message type: %ld\nMessage: %s\n", mq.m_type, mq.message);
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 27.c
rohit2026~$./a.out
Enter message type: 1
Choose  flag for msgrcv:
1. 0 (Wait/Block until a message arrives)
2. IPC_NOWAIT (Return immediately if no message is present)
Enter your choice (1 or 2): 1
Using 0 as the flag. The program will wait for a message...
Message received successfully!
Message type: 1
Message: Sending Message to queue!!
rohit2026~$gcc 27.c
rohit2026~$./a.out 
Enter message type: 1
Choose  flag for msgrcv:
1. 0 (Wait/Block until a message arrives)
2. IPC_NOWAIT (Return immediately if no message is present)
Enter your choice (1 or 2): 2
Using IPC_NOWAIT flag. The program will not wait.
Message received successfully!
Message type: 1
Message: Hello!!!
rohit2026~$./a.out 
Enter message type: 1       
Choose  flag for msgrcv:
1. 0 (Wait/Block until a message arrives)
2. IPC_NOWAIT (Return immediately if no message is present)
Enter your choice (1 or 2): 2
Using IPC_NOWAIT flag. The program will not wait.
================================================
*/