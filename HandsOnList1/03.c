/*
====================================================================================
Name : 03.c
Author : Rohitangshu Bose
Description : Write a program to create a file and print the file descriptor value. 
			  Use creat( ) system call.
Date: 1st September, 2025.
====================================================================================
*/

#include<sys/types.h>	// Import data type used in System call
#include<sys/stat.h>	// Import sys/types.h data micros
#include<fcntl.h>		// Import file Control system calls
#include<stdio.h>		// Import printf and perror

int main(int argc, char *argv[]) 
{
    if(argc != 2) 
	{
        printf("File name needed in argument\nUsage: %s <filename>\n", argv[0]);
        return 0;
    }
	
	const char *fileName = argv[1];
	int fd = creat(fileName,0644);

	if(fd == -1){
		perror("Error while creating file\n");
	}else{
		printf("File created sucessfully. File descriptor: %d\n",fd);
	}
	return 0;
}

/*
===============================================
Output:
_______________________________________________
rohit2026~$gcc 03.c            
rohit2026~$./a.out             
File name needed in arguement
: Undefined error: 0
rohit2026~$./a.out NewFile.txt 
File created sucessfully. File descriptor: 3
===============================================
*/
