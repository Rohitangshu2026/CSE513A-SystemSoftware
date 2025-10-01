/*
================================================================================================
Name        : 11.c
Author      : Rohitangshu Bose
Description : Write a program to ignore a SIGINT signal then reset the default action of the 
              SIGINT signal - use sigaction system call.
Date        : 1st October, 2025.
=================================================================================================
*/
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main() {
    struct sigaction sa;


    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = SIG_IGN;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Ignore SIGINT for the next 5 seconds....\n");
    sleep(5);

    printf("\nResetting SIGINT to default action....\n");

    sa.sa_handler = SIG_DFL;
    
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("The program will now terminate on Ctrl+C\n");
    sleep(7);

    printf("\nProgram finished without receiving SIGINT in the second phase.\n");

    return 0;
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 11.c
rohit2026~$./a.out 
Ignore SIGINT for the next 5 seconds....
^C^C

Resetting SIGINT to default action....
The program will now terminate on Ctrl+C
^C
================================================
*/