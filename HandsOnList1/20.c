/*
=====================================================================================================
Name        : 20.c
Author      : Rohitangshu Bose
Description : Find out the priority of your running program. Modify the priority with nice command.
Date        : 1st September, 2025
=====================================================================================================
*/

#include <unistd.h> 
#include <stdio.h>  
#include <stdlib.h> 

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
        printf("File name needed in arguement\nUsage: %s <filename>\n", argv[0]);
        return 0;
    }
	int modifiedPriority = atoi(argv[1]);
	int priority = nice(0);
	printf("Current Priority: %d\n",priority);
	priority = nice(modifiedPriority);
	printf("Modiefied Priority: %d\n",priority);
	return 0;
}

/*
===============================================
Output:
_______________________________________________
rohit2026~$gcc 20.c
rohit2026~$./a.out 3
Current Priority: 0
Modiefied Priority: 3
===============================================
*/
