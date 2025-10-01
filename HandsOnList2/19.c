/*
=================================================================================================
Name        : 19.c
Author      : Rohitangshu Bose
Description : Create a FIFO file by
                 d. mknod system call
                 e. mkfifo library function
Date        : 1st October, 2025.
=================================================================================================
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    if (mknod("myfifo1", S_IFIFO | 0666, 0) == -1) {
        perror("mknod error");
        return 1;
    }
    printf("FIFO file created successfully using mknod().\n");

    if (mkfifo("myfifo2", 0666) == -1) {
        perror("mkfifo error");
        return 1;
    }
    printf("FIFO file created successfully using mkfifo().\n");
    return 0;

}

/*
===================================================================
Output:
___________________________________________________________________
rohit2026~$gcc 19.c  
rohit2026~$./a.out   
FIFO file created successfully using mknod().
FIFO file created successfully using mkfifo().
====================================================================
*/
