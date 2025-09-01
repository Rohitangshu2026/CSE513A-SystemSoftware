/*
============================================================================
Name : 01_a.c
Author : Rohitangshu Bose
Description : Create a soft link file using the `symlink` system call
Date: 1st September, 2025.
============================================================================
*/

#include<unistd.h> // import symlink
#include<stdio.h>  // import printf and perror

int main(int argc, char *argv[]){

	if(argc != 3){
		printf("Enter source and target file Name in arguement\n");
		return 0;
	}
	const char *source = argv[1];
	const char *target = argv[2];

	int status = symlink(source,target);
	if(status == -1){
		perror("symlink");
		printf("Error while creating link\n");
	}else{
		printf("Link created successfully\n");
	}
	return 0;
}

/*
 > ./a.out source.txt softLink.txt 
 >  Link created successfully
*/
