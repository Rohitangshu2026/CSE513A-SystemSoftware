/*
================================================================================================
Name        : 10.c
Author      : Rohitangshu Bose
Description : Write a separate program using sigaction system call to catch the following signals.
                a. SIGSEGV
                b. SIGINT
                c. SIGFPE
Date        : 1st October, 2025.
=================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>

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
    }
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = handler;
    memset(&sa, 0, sizeof(sa));

    int choice;
    printf("Choose an option to generate a signal:\n");
    printf("1. SIGSEGV (Segmentation Fault)\n");
    printf("2. SIGINT  (Interrupt from Keyboard - Ctrl+C)\n");
    printf("3. SIGFPE  (Floating-Point Exception)\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        if (sigaction(SIGSEGV, &sa, NULL) == -1) {
            perror("sigaction");
            return 1;
        }
        printf("Generating a segmentation fault...\n");
        char *ptr = NULL;
        *ptr = 'a';
        break;

    case 2:
        if (sigaction(SIGINT, &sa, NULL) == -1) {
            perror("sigaction");
            return 1;
        }
        printf("Handler for SIGINT is set. Press Ctrl+C in the next 10 seconds.\n");
        sleep(10);
        printf("No SIGINT was received.\n");
        break;

    case 3:
        if (sigaction(SIGFPE, &sa, NULL) == -1) {
            perror("sigaction");
            return 1;
        }
        printf("Generating a floating point exception...\n");
        int x = 1;
        int y = 0;
        int result = x / y;
        (void)result;
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
rohit2026~$gcc 10.c
rohit2026~$./a.out
Choose an option to generate a signal:
1. SIGSEGV (Segmentation Fault)
2. SIGINT  (Interrupt from Keyboard - Ctrl+C)
3. SIGFPE  (Floating-Point Exception)
1
Generating a segmentation fault...
zsh: segmentation fault  ./a.out
rohit2026~$./a.out
Choose an option to generate a signal:
1. SIGSEGV (Segmentation Fault)
2. SIGINT  (Interrupt from Keyboard - Ctrl+C)
3. SIGFPE  (Floating-Point Exception)
2
Handler for SIGINT is set. Press Ctrl+C in the next 10 seconds.
^C
rohit2026~$./a.out
Choose an option to generate a signal:
1. SIGSEGV (Segmentation Fault)
2. SIGINT  (Interrupt from Keyboard - Ctrl+C)
3. SIGFPE  (Floating-Point Exception)
3
Generating a floating point exception...
================================================
*/