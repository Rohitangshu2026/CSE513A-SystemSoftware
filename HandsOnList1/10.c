/*
======================================================================================
Name        : 10_a.c
Author      : Rohitangshu Bose
Description : Write a program to open a file with read write mode, write 10 bytes,  
              move the file pointer by 10 bytes (use lseek) and write again 10 bytes.
              a. check the return value of lseek
              b. open the file with od and check the empty spaces in between the data. 
Date        : 1st September,2025
======================================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("Please provide a filename");
        return 1;
    }

    int fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    char data[] = "0123456789"; 

    if (write(fd, data, 10) != 10) {
        perror("Error writing first 10 bytes");
        close(fd);
        return 1;
    }
    printf("First 10 bytes written: %s\n", data);

    off_t offset = lseek(fd, 10, SEEK_CUR);
    if (offset == (off_t)-1) {
        perror("Error moving file pointer");
        close(fd);
        return 1;
    }
    printf("File pointer moved to offset: %lld\n", (long long)offset);

    if (write(fd, data, 10) != 10) {
        perror("Error writing second 10 bytes");
        close(fd);
        return 1;
    }
    printf("Next 10 bytes written: %s\n", data);

    offset = lseek(fd, 0, SEEK_CUR);
    if (offset == (off_t)-1) {
        perror("Error getting current offset");
    } else {
        printf("Final file offset: %lld\n", (long long)offset);
    }

    close(fd);
    return 0;
}

/*
================================================================================
Output:
________________________________________________________________________________
rohit2026~$gcc 10.c    
rohit2026~$./a.out text.txt    
First 10 bytes written: 0123456789
File pointer moved to offset: 20
Next 10 bytes written: 0123456789
Final file offset: 30
rohit2026~$cat text.txt    
01234567890123456789%   
================================================================================
*/