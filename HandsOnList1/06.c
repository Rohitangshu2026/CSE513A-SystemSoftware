/*
============================================================================
Name : 06.c
Author : Rohitangshu Bose
Description : Write a program to take input from STDIN and display on STDOUT. 
              Use only read/write system calls
Date: 1st September, 2025.
============================================================================
*/

#include <unistd.h>	
#include <stdio.h>	

int main()
{
	char buffer[1];
	int readByte,writeByte;
	while(1)
    {
		readByte = read(STDIN_FILENO,buffer,1);
		writeByte = write(STDOUT_FILENO,buffer,1);

		if(readByte == -1 || writeByte == -1)
        {
			perror("Error while reading from STDIN / writing to STDOUT\n");
			return 0;
		}
        else if(readByte == 0) 
            break; // EOF
    }
	return 0;
}

/*
===============================================
Output:
_______________________________________________
rohit2026~$gcc 06.c -o 06.out                                       
rohit2026~$./06.out                                                 
Hello World!!
Hello World!!
HI THERE!!
HI THERE!!
^D
rohit2026~$
===============================================
*/
