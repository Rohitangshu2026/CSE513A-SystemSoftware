/*
==============================================================================================
Name        : 18.c
Author      : Rohitangshu Bose
Description :  Wrie a program to perform Record locking.
                 a. Implement write lock
                 b. Implement read lock
Date        : 7th September, 2025
==============================================================================================
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define RECORD_COUNT 3
#define RECORD_SIZE sizeof(struct record)

struct record {
    int train_num;
    int ticket_count;
};

void lock_record(int fd, off_t offset, short lock_type) {
    struct flock lock;
    lock.l_type = lock_type;
    lock.l_whence = SEEK_SET;
    lock.l_start = offset;
    lock.l_len = RECORD_SIZE;
    lock.l_pid = getpid();

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error while locking record");
        _exit(1);
    }
}

void unlock_record(int fd, off_t offset) {
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = offset;
    lock.l_len = RECORD_SIZE;
    lock.l_pid = getpid();

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Error while unlocking record");
        _exit(1);
    }
}

void initialize_records(int fd) {
    struct record records[RECORD_COUNT];
    for (int i = 0; i < RECORD_COUNT; i++) {
        records[i].train_num = i + 1;
        records[i].ticket_count = 0;
    }
    lseek(fd, 0, SEEK_SET);
    write(fd, records, RECORD_SIZE * RECORD_COUNT);
}

int main() {
    const char *filePath = "record.txt";
    int fd = open(filePath, O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    if (lseek(fd, 0, SEEK_END) == 0) {
        initialize_records(fd);
        printf("Records initialized.\n");
    }

    int choice;
    printf("Choose an option:\n1. View ticket counts (read)\n2. Book a ticket (write)\nEnter: ");
    scanf("%d", &choice);
    if (choice != 1 && choice != 2) {
        printf("Invalid choice.\n");
        close(fd);
        return 1;
    }

    int input;
    printf("Select train number (1-%d): ", RECORD_COUNT);
    scanf("%d", &input);
    if (input < 1 || input > RECORD_COUNT) {
        printf("Invalid train number.\n");
        close(fd);
        return 1;
    }

    off_t offset = (input - 1) * RECORD_SIZE;

    if (choice == 1) {
        lock_record(fd, offset, F_RDLCK);
    } else {
        lock_record(fd, offset, F_WRLCK);
    }

    struct record r;
    lseek(fd, offset, SEEK_SET);
    read(fd, &r, RECORD_SIZE);

    if (choice == 1) {
        printf("Train %d: Current ticket count = %d\n", r.train_num, r.ticket_count);
    } else {
        r.ticket_count++;
        lseek(fd, offset, SEEK_SET);
        write(fd, &r, RECORD_SIZE);
        printf("Ticket booked for train %d! New ticket count = %d\n", r.train_num, r.ticket_count);
    }

    unlock_record(fd, offset);
    close(fd);

    return 0;
}

/*
================================================================================
Output:
________________________________________________________________________________
rohit2026~$gcc 18.c  
rohit2026~$./a.out 
Records initialized.
Choose an option:
1. View ticket counts (read)
2. Book a ticket (write)
Enter: 1
Select train number (1-3): 2
Train 2: Current ticket count = 0
rohit2026~$./a.out 
Choose an option:
1. View ticket counts (read)
2. Book a ticket (write)
Enter: 2
Select train number (1-3): 3
Ticket booked for train 3! New ticket count = 1
rohit2026~$./a.out
Choose an option:
1. View ticket counts (read)
2. Book a ticket (write)
Enter: 1
Select train number (1-3): 3
Train 3: Current ticket count = 1                                       
================================================================================
*/

