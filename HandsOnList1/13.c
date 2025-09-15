/*
============================================================================
Name        : 13.c
Author      : Rohitangshu Bose
Description : Write a program to wait for a STDIN for 10 seconds using select. 
              Write a proper print statement to verify whether the data is 
              available within 10 seconds or not (check in $man 2 select).
Date        : 7th September, 2025
============================================================================
*/

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() 
{
    fd_set readfds;
    struct timeval timeout;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds); 

    timeout.tv_sec = 10; 
    timeout.tv_usec = 0;

    printf("Waiting for input for 10 seconds...\n");

    int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

    if (ret == -1) 
        perror("select error");
    else if (ret == 0) 
        printf("No input within 10 seconds. Timeout occurred.\n");
    else 
        if (FD_ISSET(STDIN_FILENO, &readfds)) 
        {
            char buffer[100];
            int n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
            if (n > 0) 
            {
                buffer[n] = '\0';
                printf("You entered: %s\n", buffer);
            }
        }


    return 0;
}

/*
================================================================================
Output:
________________________________________________________________________________
rohit2026~$gcc 13.c        
rohit2026~$./a.out     
Waiting for input for 10 seconds...
hello
You entered: hello

rohit2026~$./a.out     
Waiting for input for 10 seconds...
No input within 10 seconds. Timeout occurred.                                                         
================================================================================
*/
