/*
=====================================================================
Name        : 07.c
Author      : Rohitangshu Bose
Description : Write a simple program to print the created thread ids.
Date        : 1st October, 2025.
=====================================================================
*/
#include<pthread.h>
#include<stdio.h>

void *displayThread(void *arg)
{
    printf("Thread created with id : %lu!!\n",(long unsigned)pthread_self());
    return NULL;
}

int main()
{
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, (void *)displayThread, NULL);
    pthread_create(&thread2, NULL, (void *)displayThread, NULL);
    pthread_create(&thread3, NULL, (void *)displayThread, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    return 0;
}
/*
================================================
Output:
________________________________________________
rohit2026~$gcc 07.c
rohit2026~$./a.out
Thread created with id : 6091468800!!
Thread created with id : 6092042240!!
Thread created with id : 6092615680!!
================================================
*/