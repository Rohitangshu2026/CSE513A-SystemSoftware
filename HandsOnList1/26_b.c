/*
===================================================================
Name        : 26_b.c
Author      : Rohitangshu Bose
Description : Write a program to execute an executable program
              pass some input to an executable program. 
              (for example execute an executable of $./a.out name)
Date        : 1st September, 2025
===================================================================
*/
#include <stdio.h>
#include <unistd.h>

int main() 
{
    char *exec_path = "./22.out"; 
    char *argv = "text.txt";

    printf("Executing %s with argument: %s\n", exec_path, argv);

    if (execl(exec_path, exec_path, argv, NULL) == -1)
        perror("execl failed");

    printf("Execution finished.\n");

    return 0;
}

/*
==================================================
Output:
__________________________________________________
rohit2026~$gcc 22.c -o 22.out
rohit2026~$gcc 26_b.c        
rohit2026~$./a.out           
Executing ./22.out with argument: text.txt
rohit2026~$cat text.txt
Writing in Parent
Writing in Child
=================================================
*/
