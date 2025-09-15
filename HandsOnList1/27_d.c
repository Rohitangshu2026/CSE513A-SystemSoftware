/*
================================================================================
Name        : 27_d.c
Author      : Rohitangshu Bose
Description : Write a program to execute ls -Rl by using the system call execv
Date        : 1st September, 2025
================================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main() 
{
    char *args[] = {"ls", "-Rl", NULL};
    if (execv("/bin/ls", args) == -1)
        perror("execv failed");
    printf("Execution finished.\n");

    return 0;
}

/*
==============================================================================
Output:
______________________________________________________________________________
rohit2026~$gcc 27_d.c
rohit2026~$./a.out   
total 936
-rw-r--r--@ 1 rohit2026  staff   1322  7 Sep 12:44 01_a.c
-rwxr-xr-x  1 rohit2026  staff  33512  2 Sep 15:17 01_a.out
-rw-r--r--@ 1 rohit2026  staff   4257  7 Sep 14:02 02.c
-rwxr-xr-x  1 rohit2026  staff  16840  7 Sep 13:58 02.out
-rw-r--r--@ 1 rohit2026  staff   1304  7 Sep 15:28 03.c
-rw-r--r--@ 1 rohit2026  staff   1238  7 Sep 14:29 04.c
-rwxr-xr-x  1 rohit2026  staff  33512  7 Sep 14:27 04.out
-rw-r--r--@ 1 rohit2026  staff   3677  7 Sep 15:06 05.c
-rwxr-xr-x  1 rohit2026  staff  33560  7 Sep 14:45 05.out
-rw-r--r--@ 1 rohit2026  staff   1126  7 Sep 15:24 06.c
-rwxr-xr-x  1 rohit2026  staff  33512  7 Sep 15:23 06.out
-rw-r--r--@ 1 rohit2026  staff   5814  7 Sep 15:45 07.c
-rwxr-xr-x  1 rohit2026  staff  33768  7 Sep 15:39 07.out
-rw-r--r--@ 1 rohit2026  staff   2163  7 Sep 16:06 08.c
-rwxr-xr-x  1 rohit2026  staff  33592  7 Sep 15:46 08.out
-rw-r--r--@ 1 rohit2026  staff   1101  7 Sep 16:19 19.c
-rwxr-xr-x  1 rohit2026  staff  16840  7 Sep 13:57 2.out
-rw-r--r--@ 1 rohit2026  staff   1062  7 Sep 16:33 20.c
-rw-r--r--@ 1 rohit2026  staff    825  7 Sep 16:37 21.c
-rw-r--r--@ 1 rohit2026  staff   1483  7 Sep 18:02 22.c
-rwxr-xr-x  1 rohit2026  staff  33640  7 Sep 18:00 22.out
-rw-r--r--@ 1 rohit2026  staff   1334  7 Sep 17:12 23.c
-rw-r--r--@ 1 rohit2026  staff   1120  7 Sep 17:17 24.c
-rw-r--r--@ 1 rohit2026  staff   2412  7 Sep 17:46 25.c
-rwxr-xr-x  1 rohit2026  staff  33688  7 Sep 17:50 25.out
-rw-r--r--@ 1 rohit2026  staff   1131  7 Sep 18:02 26_a.c
-rw-r--r--@ 1 rohit2026  staff   1101  7 Sep 18:03 26_b.c
-rw-r--r--@ 1 rohit2026  staff   2992  7 Sep 18:08 27_a.c
-rw-r--r--@ 1 rohit2026  staff   3047  7 Sep 18:12 27_b.c
-rw-r--r--@ 1 rohit2026  staff   3116  7 Sep 18:16 27_c.c
-rw-r--r--@ 1 rohit2026  staff   3132  7 Sep 18:21 27_d.c
-rwxr-xr-x  1 rohit2026  staff  33640  7 Sep 18:22 a.out
-rw-r--r--  1 rohit2026  staff      0  7 Sep 14:49 file1.txt
-rw-r--r--  1 rohit2026  staff      0  7 Sep 14:49 file2.txt
-rw-r--r--  1 rohit2026  staff      0  7 Sep 14:49 file3.txt
-rw-r--r--  1 rohit2026  staff      0  7 Sep 14:49 file4.txt
-rw-r--r--  1 rohit2026  staff      0  7 Sep 14:49 file5.txt
-rw-r--r--  1 rohit2026  staff   4292  7 Sep 16:47 NewFile.txt
lrwxr-xr-x  1 rohit2026  staff     10  2 Sep 15:12 symLink.txt -> source.txt
-rw-r--r--  1 rohit2026  staff     70  7 Sep 18:00 text.txt
==============================================================================
*/