/*
=====================================================================================================
Name        : 22.c
Author      : Rohitangshu Bose
Description : Write a program, open a file, call fork, and then write to the file by both the child 
              as well as the parent processes. Check output of the file.
Date        : 1st September, 2025
=====================================================================================================
*/
#include <unistd.h>     
#include <sys/types.h>  
#include <sys/stat.h>   
#include <fcntl.h>      
#include <stdio.h>      

int main(int argc, char *argv[]) 
{
    if(argc < 2) 
    {
        printf("File name needed in arguement\nUsage: %s <source_file>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR | O_CREAT | O_APPEND, 0644);
    if(fd == -1) 
    {
        perror("Error opening source file");
        return 1;
    }

    pid_t pid = fork();
    if(pid < 0) 
    {
        perror("failed to fork");
        close(fd);
        return 1;
    } 
    else if(pid > 0) 
        write(fd, "Writing in Parent\n", 18);
    else
        write(fd, "Writing in Child\n", 17);
 

    close(fd);
    return 0;
}

/*
===============================================
Output:
_______________________________________________
rohit2026~$gcc 22.c           
rohit2026~$./a.out text.txt   
rohit2026~$cat text.txt
Writing in Parent
Writing in Child
===============================================
*/

