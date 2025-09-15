/*
=========================================================================================
Name        : 30.c
Author      : Rohitangshu Bose
Description : Write a program to run a script at a specific time using a Daemon process.
Date        : 7th September, 2025
=========================================================================================
*/

#include <time.h>     
#include <stdio.h>     
#include <sys/types.h> 
#include <unistd.h>    
#include <stdlib.h>    

void executeScript()
{
    char *script = "./30.sh";
    execl(script, script, NULL);
    perror("execl failed");
    exit(1);
}


int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Enter time as arguement\nUsage: [hour] [minutes] [seconds]  \n");
        return 0;
    }
    time_t now;
    struct tm *target;
    time_t target_time;

    time(&now);
    target = localtime(&now);

    target->tm_hour = atoi(argv[1]);
    target->tm_min  = (argc > 2) ? atoi(argv[2]) : 0;
    target->tm_sec  = (argc > 3) ? atoi(argv[3]) : 0;

    target_time = mktime(target);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        setsid();

        if (difftime(target_time, now) <= 0) {
            fprintf(stderr, "Target time has already passed\n");
            exit(0);
        }

        while (1) {
            time(&now);
            if (difftime(target_time, now) <= 0) {
                printf("Launching script via daemon process...\n");
                executeScript();
                break;
            }
            sleep(1);
        }
    }

    return 0;
}

/*
================================================================================
Output:
________________________________________________________________________________
rohit2026~$gcc 30.c
rohit2026~$./a.out 22 34 40
rohit2026~$Launching script via daemon process...
total 1184
-rw-r--r--@ 1 rohit2026  staff   1322  7 Sep 12:44 01_a.c
-rwxr-xr-x  1 rohit2026  staff  33512  2 Sep 15:17 01_a.out
-rw-r--r--@ 1 rohit2026  staff   1071  7 Sep 21:58 01_b.c
-rw-r--r--@ 1 rohit2026  staff   1347  7 Sep 22:00 01_c.c
-rw-r--r--@ 1 rohit2026  staff    239  7 Sep 22:02 01_sh.sh
-rw-r--r--@ 1 rohit2026  staff   4257  7 Sep 14:02 02.c
-rwxr-xr-x  1 rohit2026  staff  16840  7 Sep 13:58 02.out
-rw-r--r--@ 1 rohit2026  staff   1304  7 Sep 15:28 03.c
-rw-r--r--@ 1 rohit2026  staff   1238  7 Sep 14:29 04.c
-rwxr-xr-x  1 rohit2026  staff  33512  7 Sep 14:27 04.out
-rw-r--r--@ 1 rohit2026  staff   3677  7 Sep 15:06 05.c
-rwxr-xr-x  1 rohit2026  staff  33560  7 Sep 14:45 05.out
-rw-r--r--@ 1 rohit2026  staff   1126  7 Sep 15:24 06.c
-rwxr-xr-x  1 rohit2026  staff  33512  7 Sep 15:23 06.out
-rw-r--r--@ 1 rohit2026  staff   6113  7 Sep 22:05 07.c
-rwxr-xr-x  1 rohit2026  staff  33768  7 Sep 15:39 07.out
-rw-r--r--@ 1 rohit2026  staff   6117  7 Sep 22:12 08.c
-rwxr-xr-x  1 rohit2026  staff  33592  7 Sep 15:46 08.out
-rw-r--r--@ 1 rohit2026  staff   2490  7 Sep 20:06 09.c
-rw-r--r--@ 1 rohit2026  staff   2299  7 Sep 22:19 10.c
-rw-r--r--@ 1 rohit2026  staff   1965  7 Sep 20:37 11_a.c
-rw-r--r--@ 1 rohit2026  staff   1984  7 Sep 20:38 11_b.c
-rw-r--r--@ 1 rohit2026  staff   2044  7 Sep 20:42 11_c.c
-rw-r--r--@ 1 rohit2026  staff   1966  7 Sep 20:47 12.c
-rw-r--r--@ 1 rohit2026  staff   1874  7 Sep 20:55 13.c
-rw-r--r--@ 1 rohit2026  staff   1801  7 Sep 21:00 14.c
-rw-r--r--@ 1 rohit2026  staff   2014  7 Sep 21:02 15.c
-rw-r--r--@ 1 rohit2026  staff   2250  7 Sep 21:34 16_a.c
-rw-r--r--@ 1 rohit2026  staff   1977  7 Sep 21:26 16_b.c
-rw-r--r--@ 1 rohit2026  staff   1640  7 Sep 21:41 17_a.c
-rw-r--r--@ 1 rohit2026  staff   2396  7 Sep 21:42 17_b.c
-rw-r--r--@ 1 rohit2026  staff   3897  7 Sep 21:52 18.c
-rw-r--r--@ 1 rohit2026  staff   1524  7 Sep 22:25 19.c
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
-rw-r--r--@ 1 rohit2026  staff   3190  7 Sep 18:22 27_d.c
-rw-r--r--@ 1 rohit2026  staff   3246  7 Sep 18:25 27_e.c
-rw-r--r--@ 1 rohit2026  staff   1106  7 Sep 19:12 28.c
-rw-r--r--@ 1 rohit2026  staff   2575  7 Sep 19:21 29.c
-rw-r--r--@ 1 rohit2026  staff   1738  7 Sep 22:34 30.c
-rwxrwxrwx@ 1 rohit2026  staff    243  7 Sep 22:28 30.sh
-rwxr-xr-x  1 rohit2026  staff  34056  7 Sep 22:34 a.out
-rw-r--r--  1 rohit2026  staff   8599  7 Sep 19:52 daemon_log.txt
-rwxr--r--  1 rohit2026  staff      4  7 Sep 21:41 db
-rw-r--r--  1 rohit2026  staff      0  7 Sep 14:49 file1.txt
-rw-r--r--  1 rohit2026  staff      0  7 Sep 14:49 file2.txt
-rw-r--r--  1 rohit2026  staff      0  7 Sep 14:49 file3.txt
-rw-r--r--  1 rohit2026  staff      0  7 Sep 14:49 file4.txt
-rw-r--r--  1 rohit2026  staff      0  7 Sep 14:49 file5.txt
prwx------  1 rohit2026  staff      0  7 Sep 22:00 mkfifo
prwx------  1 rohit2026  staff      0  7 Sep 22:00 mknod
-rw-r--r--  2 rohit2026  staff   4257  7 Sep 22:06 NewFile.txt
-rw-r--r--  1 rohit2026  staff     24  7 Sep 21:52 record.txt
lrwxr-xr-x  1 rohit2026  staff     10  2 Sep 15:12 symLink.txt -> source.txt
-rw-r--r--  2 rohit2026  staff   4257  7 Sep 22:06 test.txt
-rw-------  1 rohit2026  staff     30  7 Sep 22:18 text.txt
-rwxr--r--  1 rohit2026  staff      4  7 Sep 21:08 ticket_db
================================================================================
*/
