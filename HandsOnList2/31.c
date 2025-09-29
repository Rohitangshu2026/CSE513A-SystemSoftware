/*
===============================================================================
Name 		: 31.c
Author 		: Rohitangshu Bose
Description : Write a program to create a semaphore and initialize value to 
			  the semaphore.
				a. create a binary semaphore
				b. create a counting semaphore
Date		: 17th September, 2025.
===============================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

typedef union
{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
}semun;

int main()
{
	key_t key;
	int semid;
	semun arg;
	int choice,count;
	
	key = ftok(".", 'L');
    if (key == -1) 
	{
        perror("ftok() failed");
        exit(1);
    }

	semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) 
	{
        perror("semget() failed");
        exit(1);
    }
    
    printf("Semaphore created with ID: %d\n", semid);

	printf("1. Press 1 for Binary Semaphore\n2. Press 2 for Counting Semaphore\nEnter choice : ");
	scanf("%d", &choice);
	
	switch(choice)
	{
		case 1 : 
			count = 1;
			arg.val = count;
			printf("Binary Semaphore initialized\n");
			break;
		case 2 :  
			printf("Enter Counting Semaphore value: ");
			scanf("%d", &count);
			arg.val = count;
			printf("Counting Semaphore initialized\n");
			break;
		default :  
		 	printf("Choice Invalid!!");
	}
	
	semctl(semid, 0 , SETVAL, arg);
	return 0;
}
		
/*
===============================================
Output:
_______________________________________________
rohit2026~$gcc 31.c
rohit2026~$./a.out 
Semaphore created with ID: 65536
1. Press 1 for Binary Semaphore
2. Press 2 for Counting Semaphore
Enter choice : 1
Binary Semaphore initialized
rohit2026~$./a.out 
Semaphore created with ID: 65536
1. Press 1 for Binary Semaphore
2. Press 2 for Counting Semaphore
Enter choice : 2   
Enter Counting Semaphore value: 5
Counting Semaphore initialized
===============================================
*/
