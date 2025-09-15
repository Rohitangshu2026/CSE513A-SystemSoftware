/*
==============================================================
Name        : 26_a.c
Author      : Rohitangshu Bose
Description : Write a program to execute an executable program
              (use some executable program)
Date        : 1st September, 2025
==============================================================
*/
#include <stdio.h>
#include <unistd.h>

int main() 
{
    char *exec_path = "./25.out"; 

    printf("Executing %s ...\n", exec_path);

    if (execl(exec_path, exec_path, NULL) == -1)
        perror("execl failed");

    printf("Execution finished.\n");

    return 0;
}

/*
==================================================
Output:
__________________________________________________
rohit2026~$gcc 26_a.c
rohit2026~$./a.out   
Executing ./25.out ...
Child A created! PID: 3665
Child A put to sleep for 2s! 3665
Parent waiting for Child C (PID: 3667)...
Child B created! PID: 3666
Child A put to sleep for 4s! 3666
Child C created! PID: 3667
Child A put to sleep for 8s! 3667
Child A exits!
Child B exits!
Child C exits!
Child C exited with status: 0
=================================================
*/
