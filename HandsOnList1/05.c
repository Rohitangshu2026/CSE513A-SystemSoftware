/*
============================================================================
Name        : 05.c
Author      : Rohitangshu Bose
Description : Write a program to create five new files with infinite loop. 
              Execute the program in the background and 
              check the file descriptor table at /proc/pid/fd.
Date        : 1st September, 2025
============================================================================
*/

#include <sys/types.h>	
#include <sys/stat.h>	
#include <fcntl.h>
#include <stdio.h>	
#include <unistd.h>

int main()
{
    for( ; ; )
    {
        int fd1 = creat("file1.txt",0644);
        int fd2 = creat("file2.txt",0644);
        int fd3 = creat("file3.txt",0644);
        int fd4 = creat("file4.txt",0644);
        int fd5 = creat("file5.txt",0644);

        printf("%d %d %d %d %d\n",fd1,fd2,fd3,fd4,fd5);
        sleep(10);

		close(fd1);
		close(fd2);
		close(fd3);
		close(fd4);
		close(fd5);
        
    }
    return 0;
}

// Note: Since macOS does not have a /proc filesystem like Linux, so using lsof command instead

/*
=======================================================================================================================================================
Output(On macOS):
_______________________________________________________________________________________________________________________________________________________
rohit2026~$gcc 05.c -o 05.out
rohit2026~$./05.out &
[3] 2592
rohit2026~$3 4 5 6 7
3 4 5 6 7
3 4 5 6 7
3 4 5 6 7
lsof -p 2592
COMMAND  PID      USER   FD   TYPE DEVICE SIZE/OFF                NODE NAME
05.out  2592 rohit2026  cwd    DIR   1,16      672             2735475 /Users/rohit2026/Documents/MTech/Term I/Systems Software/HandsOnList1
05.out  2592 rohit2026  txt    REG   1,16    33560             3058191 /Users/rohit2026/Documents/MTech/Term I/Systems Software/HandsOnList1/05.out
05.out  2592 rohit2026  txt    REG   1,16  2289328 1152921500312524573 /usr/lib/dyld
05.out  2592 rohit2026    0u   CHR   16,0  0t69536                 707 /dev/ttys000
05.out  2592 rohit2026    1u   CHR   16,0  0t69536                 707 /dev/ttys000
05.out  2592 rohit2026    2u   CHR   16,0  0t69536                 707 /dev/ttys000
05.out  2592 rohit2026    3w   REG   1,16        0             3057684 /Users/rohit2026/Documents/MTech/Term I/Systems Software/HandsOnList1/file1.txt
05.out  2592 rohit2026    4w   REG   1,16        0             3057685 /Users/rohit2026/Documents/MTech/Term I/Systems Software/HandsOnList1/file2.txt
05.out  2592 rohit2026    5w   REG   1,16        0             3057686 /Users/rohit2026/Documents/MTech/Term I/Systems Software/HandsOnList1/file3.txt
05.out  2592 rohit2026    6w   REG   1,16        0             3057687 /Users/rohit2026/Documents/MTech/Term I/Systems Software/HandsOnList1/file4.txt
05.out  2592 rohit2026    7w   REG   1,16        0             3057688 /Users/rohit2026/Documents/MTech/Term I/Systems Software/HandsOnList1/file5.txt
=======================================================================================================================================================
Output(On WSL):
_______________________________________________________________________________________________________________________________________________________
ayushi@Entropy:~/HandsOnList1$ gcc 05.c -o 05.out
ayushi@Entropy:~/HandsOnList1$ ./05.out &
[4] 1858
ayushi@Entropy:~/HandsOnList1$ 3 4 5 6 7
3 4 5 6 7
3 4 5 6 7
3 4 5 6 7
3 4 5 6 7
ls /proc/1858/fd
0  1  2  3  4  5  6  7
=======================================================================================================================================================
*/
