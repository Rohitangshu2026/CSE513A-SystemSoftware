/*
============================================================================
Name        : 25.c
Author      : Rohitangshu Bose
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
                i.    Access permission
                ii.   uid, gid
                iii.  Time of last message sent and received
                iv.   Time of last change in the message queue
                v.    Size of the queue
                vi.   Number of messages in the queue
                vii.  Maximum number of bytes allowed
                viii. PID of the msgsnd and msgrcv
Date        : 30th September, 2025.
============================================================================
*/

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>

int main()
{
    key_t key = ftok(".", 'a');
    int msqid = msgget(key, IPC_CREAT | 0666);
    
    struct msqid_ds mq;
    msgctl(msqid, IPC_STAT, &mq);

    printf("Access Permissions                      : %o\n", mq.msg_perm.mode);
    printf("Uid and gid of owner                    : %d %d\n", mq.msg_perm.uid, mq.msg_perm.gid);
    printf("Uid and gid of creator                  : %d %d\n", mq.msg_perm.cuid, mq.msg_perm.cgid);
    printf("Time of last message sent and received  : %ld %ld\n", mq.msg_stime, mq.msg_rtime);
    printf("Time of last change in the queue        : %ld\n", mq.msg_ctime);
    printf("Size of the queue                       : %ld\n", mq.msg_cbytes);
    printf("Number of messages in queue             : %ld\n", mq.msg_qnum);
    printf("Max number of bytes allowed in queue    : %ld\n", mq.msg_qbytes);
    printf("Pid of the last msgsnd and msgrcv       : %d %d\n", mq.msg_lspid, mq.msg_lrpid);

    return (0);
}

/*
=====================================================
Output:
_____________________________________________________
rohit2026~$gcc 25.c
rohit2026~$./a.out 
Access Permissions                      : 666
Uid and gid of owner                    : 501 20
Uid and gid of creator                  : 501 20
Time of last message sent and received  : 0 0
Time of last change in the queue        : 1759204631
Size of the queue                       : 0
Number of messages in queue             : 0
Max number of bytes allowed in queue    : 2048
Pid of the last msgsnd and msgrcv       : 0 0
=====================================================
*/