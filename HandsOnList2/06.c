/*
=============================================================
Name        : 06.c
Author      : Rohitangshu Bose
Description : Write a simple program to create three threads.
Date        : 1st October, 2025.
=============================================================
*/
#include<pthread.h>
#include<stdio.h>

void displayThread(void)
{
    printf("Thread created!!\n");
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
rohit2026~$gcc 06.c
rohit2026~$./a.out
Thread created!!
Thread created!!
Thread created!!
================================================
*/