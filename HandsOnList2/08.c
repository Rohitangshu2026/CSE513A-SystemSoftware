/*
================================================================================================
Name        : 08.c
Author      : Rohitangshu Bose
Description : Write a separate program using signal system call to catch the following signals.
                a. SIGSEGV
                b. SIGINT
                c. SIGFPE
                d. SIGALRM (use alarm system call)
                e. SIGALRM (use setitimer system call)
                f. SIGVTALRM (use setitimer system call)
                g. SIGPROF (use setitimer system call)
Date        : 1st October, 2025.
=================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<unistd.h>
#include<signal.h>

void handler(int signum)
{
    switch (signum)
    {
    case SIGSEGV:
        printf("Caught segmentation fault (SIGSEGV)!\n");
        _exit(1);
    case SIGINT:
        printf("\nCaught keyboard interrupt (SIGINT)!\n");
        _exit(0);
    case SIGFPE:
        printf("Caught floating point exception (SIGFPE)!\n");
        _exit(2);
    case SIGALRM:
        printf("Caught ALARM signal (SIGALRM)\n");
        break;
    case SIGVTALRM:
        printf("Caught VIRTUAL ALARM signal (SIGVTALRM)\n");
        break;
    case SIGPROF:
        printf("Caught PROFILING ALARM signal (SIGPROF)\n");
        break;
    }
}

int main()
{
    int choice;
    printf("Choose an option to generate a signal:\n");
    printf("1. SIGSEGV (Segmentation Fault)\n");
    printf("2. SIGINT  (Interrupt from Keyboard - Ctrl+C)\n");
    printf("3. SIGFPE  (Floating-Point Exception)\n");
    printf("4. SIGALRM (using alarm() call)\n");
    printf("5. SIGALRM (using setitimer() - REAL)\n");
    printf("6. SIGVTALRM (using setitimer() - VIRTUAL)\n");
    printf("7. SIGPROF (using setitimer() - PROFILING)\n");
    scanf("%d", &choice);

    switch (choice){
    case 1:
        signal(SIGSEGV, handler);
        printf("Generating a segmentation fault by writing to a NULL pointer...\n");
        char *ptr = NULL;
        *ptr = 'a';
        break;

    case 2:
        signal(SIGINT, handler);
        printf("Handler for SIGINT is set. Press Ctrl+C in the next 10 seconds.\n");
        sleep(10);
        printf("No SIGINT received.\n");
        break;

    case 3:
        signal(SIGFPE, handler);
        printf("Generating a floating point exception...\n");
        int x = 1;
        int y = 0;
        int result = x / y;
        (void)result;
        break;

    case 4:
        signal(SIGALRM, handler);
        printf("Setting a one-time alarm for 2 seconds.\n");
        alarm(2);
        printf("Waiting for alarm...\n");
        pause();
        printf("Signal handled.\n");
        break;

    case 5:
    case 6:
    case 7:
        {
            struct itimerval timer;
            timer.it_value.tv_sec = 2;
            timer.it_value.tv_usec = 0;
            timer.it_interval.tv_sec = 2;
            timer.it_interval.tv_usec = 0;

            if (choice == 5) {
                signal(SIGALRM, handler);
                printf("Setting repeating ITIMER_REAL every 2 seconds.\n");
                setitimer(ITIMER_REAL, &timer, NULL);
            } else if (choice == 6) {
                signal(SIGVTALRM, handler);
                printf("Setting repeating ITIMER_VIRTUAL every 2 seconds of CPU time.\n");
                setitimer(ITIMER_VIRTUAL, &timer, NULL);
            } else {
                signal(SIGPROF, handler);
                printf("Setting repeating ITIMER_PROF every 2 seconds of process time.\n");
                setitimer(ITIMER_PROF, &timer, NULL);
            }
            while (1);
        }
        break;

    default:
        printf("Invalid choice.\n");
        break;
    }

    return 0;
}


/*
================================================
Output:
________________________________________________
rohit2026~$gcc 08.c
rohit2026~$./a.out
Choose an option to generate a signal:
1. SIGSEGV (Segmentation Fault)
2. SIGINT  (Interrupt from Keyboard - Ctrl+C)
3. SIGFPE  (Floating-Point Exception)
4. SIGALRM (using alarm() call)
5. SIGALRM (using setitimer() - REAL)
6. SIGVTALRM (using setitimer() - VIRTUAL)
7. SIGPROF (using setitimer() - PROFILING)
1
Generating a segmentation fault by writing to a NULL pointer...
Caught segmentation fault (SIGSEGV)!
rohit2026~$./a.out
Choose an option to generate a signal:
1. SIGSEGV (Segmentation Fault)
2. SIGINT  (Interrupt from Keyboard - Ctrl+C)
3. SIGFPE  (Floating-Point Exception)
4. SIGALRM (using alarm() call)
5. SIGALRM (using setitimer() - REAL)
6. SIGVTALRM (using setitimer() - VIRTUAL)
7. SIGPROF (using setitimer() - PROFILING)
2
Handler for SIGINT is set. Press Ctrl+C in the next 10 seconds.
^C
Caught keyboard interrupt (SIGINT)!
rohit2026~$./a.out
Choose an option to generate a signal:
1. SIGSEGV (Segmentation Fault)
2. SIGINT  (Interrupt from Keyboard - Ctrl+C)
3. SIGFPE  (Floating-Point Exception)
4. SIGALRM (using alarm() call)
5. SIGALRM (using setitimer() - REAL)
6. SIGVTALRM (using setitimer() - VIRTUAL)
7. SIGPROF (using setitimer() - PROFILING)
3
Generating a floating point exception...
rohit2026~$./a.out
Choose an option to generate a signal:
1. SIGSEGV (Segmentation Fault)
2. SIGINT  (Interrupt from Keyboard - Ctrl+C)
3. SIGFPE  (Floating-Point Exception)
4. SIGALRM (using alarm() call)
5. SIGALRM (using setitimer() - REAL)
6. SIGVTALRM (using setitimer() - VIRTUAL)
7. SIGPROF (using setitimer() - PROFILING)
4
Setting a one-time alarm for 2 seconds.
Waiting for alarm...
Caught ALARM signal (SIGALRM)
Signal handled.
rohit2026~$./a.out
Choose an option to generate a signal:
1. SIGSEGV (Segmentation Fault)
2. SIGINT  (Interrupt from Keyboard - Ctrl+C)
3. SIGFPE  (Floating-Point Exception)
4. SIGALRM (using alarm() call)
5. SIGALRM (using setitimer() - REAL)
6. SIGVTALRM (using setitimer() - VIRTUAL)
7. SIGPROF (using setitimer() - PROFILING)
5
Setting repeating ITIMER_REAL every 2 seconds.
Caught ALARM signal (SIGALRM)
Caught ALARM signal (SIGALRM)
^C
rohit2026~$./a.out
Choose an option to generate a signal:
1. SIGSEGV (Segmentation Fault)
2. SIGINT  (Interrupt from Keyboard - Ctrl+C)
3. SIGFPE  (Floating-Point Exception)
4. SIGALRM (using alarm() call)
5. SIGALRM (using setitimer() - REAL)
6. SIGVTALRM (using setitimer() - VIRTUAL)
7. SIGPROF (using setitimer() - PROFILING)
6
Setting repeating ITIMER_VIRTUAL every 2 seconds of CPU time.
Caught VIRTUAL ALARM signal (SIGVTALRM)
Caught VIRTUAL ALARM signal (SIGVTALRM)
^C
rohit2026~$./a.out
Choose an option to generate a signal:
1. SIGSEGV (Segmentation Fault)
2. SIGINT  (Interrupt from Keyboard - Ctrl+C)
3. SIGFPE  (Floating-Point Exception)
4. SIGALRM (using alarm() call)
5. SIGALRM (using setitimer() - REAL)
6. SIGVTALRM (using setitimer() - VIRTUAL)
7. SIGPROF (using setitimer() - PROFILING)
7
Setting repeating ITIMER_PROF every 2 seconds of process time.
Caught PROFILING ALARM signal (SIGPROF)
Caught PROFILING ALARM signal (SIGPROF)
^C
================================================
*/