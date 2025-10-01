/*
================================================================================================
Name        : 09.c
Author      : Rohitangshu Bose
Description : Write a program to ignore a SIGINT signal then reset the default action of the 
              SIGINT signal - Use signal system call.
Date        : 1st October, 2025.
=================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int main(){
    printf("Ignore SIGINT signal.........................\n");
    signal(SIGINT, SIG_IGN);
    sleep(5);
    printf("\nReseting to default action of SIGINT signal\n");
    signal(SIGINT, SIG_DFL);
    sleep(5);
    return(0);
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 09.c
rohit2026~$./a.out
Ignore SIGINT signal.........................

Reseting to default action of SIGINT signal
rohit2026~$./a.out
Ignore SIGINT signal.........................
 
Reseting to default action of SIGINT signal
^C
rohit2026~$./a.out
Ignore SIGINT signal.........................
^C

Reseting to default action of SIGINT signal
^C

================================================
*/