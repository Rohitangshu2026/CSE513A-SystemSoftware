/*
================================================================================
Name        : 27_c.c
Author      : Rohitangshu Bose
Description : Write a program to execute ls -Rl by using the system call execle
Date        : 1st September, 2025
================================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main() 
{

    if (execle("/bin/ls", "ls", "-Rl", NULL, NULL) == -1)
        perror("execle failed");
    printf("Execution finished.\n");

    return 0;
}

/*
==============================================================================
Output:
______________________________________________________________________________
rohit2026~$gcc 27_c.c
rohit2026~$./a.out   
total 928
-rw-r--r--@ 1 rohit2026  staff   1322 Sep  7 12:44 01_a.c
-rwxr-xr-x  1 rohit2026  staff  33512 Sep  2 15:17 01_a.out
-rw-r--r--@ 1 rohit2026  staff   4257 Sep  7 14:02 02.c
-rwxr-xr-x  1 rohit2026  staff  16840 Sep  7 13:58 02.out
-rw-r--r--@ 1 rohit2026  staff   1304 Sep  7 15:28 03.c
-rw-r--r--@ 1 rohit2026  staff   1238 Sep  7 14:29 04.c
-rwxr-xr-x  1 rohit2026  staff  33512 Sep  7 14:27 04.out
-rw-r--r--@ 1 rohit2026  staff   3677 Sep  7 15:06 05.c
-rwxr-xr-x  1 rohit2026  staff  33560 Sep  7 14:45 05.out
-rw-r--r--@ 1 rohit2026  staff   1126 Sep  7 15:24 06.c
-rwxr-xr-x  1 rohit2026  staff  33512 Sep  7 15:23 06.out
-rw-r--r--@ 1 rohit2026  staff   5814 Sep  7 15:45 07.c
-rwxr-xr-x  1 rohit2026  staff  33768 Sep  7 15:39 07.out
-rw-r--r--@ 1 rohit2026  staff   2163 Sep  7 16:06 08.c
-rwxr-xr-x  1 rohit2026  staff  33592 Sep  7 15:46 08.out
-rw-r--r--@ 1 rohit2026  staff   1101 Sep  7 16:19 19.c
-rwxr-xr-x  1 rohit2026  staff  16840 Sep  7 13:57 2.out
-rw-r--r--@ 1 rohit2026  staff   1062 Sep  7 16:33 20.c
-rw-r--r--@ 1 rohit2026  staff    825 Sep  7 16:37 21.c
-rw-r--r--@ 1 rohit2026  staff   1483 Sep  7 18:02 22.c
-rwxr-xr-x  1 rohit2026  staff  33640 Sep  7 18:00 22.out
-rw-r--r--@ 1 rohit2026  staff   1334 Sep  7 17:12 23.c
-rw-r--r--@ 1 rohit2026  staff   1120 Sep  7 17:17 24.c
-rw-r--r--@ 1 rohit2026  staff   2412 Sep  7 17:46 25.c
-rwxr-xr-x  1 rohit2026  staff  33688 Sep  7 17:50 25.out
-rw-r--r--@ 1 rohit2026  staff   1131 Sep  7 18:02 26_a.c
-rw-r--r--@ 1 rohit2026  staff   1101 Sep  7 18:03 26_b.c
-rw-r--r--@ 1 rohit2026  staff   2992 Sep  7 18:08 27_a.c
-rw-r--r--@ 1 rohit2026  staff   3047 Sep  7 18:12 27_b.c
-rw-r--r--@ 1 rohit2026  staff   3058 Sep  7 18:15 27_c.c
-rw-r--r--  1 rohit2026  staff   4292 Sep  7 16:47 NewFile.txt
-rwxr-xr-x  1 rohit2026  staff  33512 Sep  7 18:15 a.out
-rw-r--r--  1 rohit2026  staff      0 Sep  7 14:49 file1.txt
-rw-r--r--  1 rohit2026  staff      0 Sep  7 14:49 file2.txt
-rw-r--r--  1 rohit2026  staff      0 Sep  7 14:49 file3.txt
-rw-r--r--  1 rohit2026  staff      0 Sep  7 14:49 file4.txt
-rw-r--r--  1 rohit2026  staff      0 Sep  7 14:49 file5.txt
lrwxr-xr-x  1 rohit2026  staff     10 Sep  2 15:12 symLink.txt -> source.txt
-rw-r--r--  1 rohit2026  staff     70 Sep  7 18:00 text.txt
==============================================================================
*/
