/*
============================================================================
Name : 04.c
Author : Rohitangshu Bose
Description : Write a program to open an existing file with read write mode. 
              Try O_EXCL flag also.
Date: 1st September, 2025.
============================================================================
*/

#include <sys/types.h>	
#include <sys/stat.h>	
#include <fcntl.h>	    
#include <stdio.h>	    

int main(int argc, char *argv[]) 
{
    if(argc != 2) 
	{
        printf("File name needed\nUsage: %s <filename>\n", argv[0]);
        return 0;
    }

	const char *fileName = argv[1];
	int fd = open(fileName, O_RDWR | O_CREAT | O_EXCL, 0644);

	if(fd == -1)
		perror("Error while opening file!\n");
    else 
		printf("Sucessfully opened file with Read and Write Mode\n");
	return 0;
}

/*
===============================================
Output:
_______________________________________________
rohit2026~$gcc 04.c -o 04.out
rohit2026~$./04.out          
File name needed
Usage: ./04.out <filename>
rohit2026~$./04.out NewFile.txt
Sucessfully opened file with Read and Write Mode
rohit2026~$./04.out NewFile.txt
Error while opening file!
: File exists
===============================================
*/