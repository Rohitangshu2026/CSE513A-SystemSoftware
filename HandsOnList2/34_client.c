/*
============================================================================
Name        : 34_client.c
Author      : Rohitangshu Bose
Description : Write a program to create a concurrent server.
                a. use fork
                b. use pthread_create
Date        : 1st October, 2025.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1"
#define PORT_NO 8080
#define BUFFER_SIZE 1024

int main() {
    int sd;
    struct sockaddr_in serv;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_written, bytes_read;

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully.\n");

    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT_NO);
    serv.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(sd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("connect failed");
        close(sd);
        exit(EXIT_FAILURE);
    }
    printf("Connected to the server at %s:%d\n", SERVER_IP, PORT_NO);

    printf("Enter a message to send to the server: ");
    scanf("%[^\n]%*c", buffer);

    bytes_written = write(sd, buffer, strlen(buffer));
    if (bytes_written < 0) {
        perror("write failed");
        close(sd);
        exit(EXIT_FAILURE);
    }
    printf("Message sent: '%s'\n", buffer);

    memset(buffer, 0, BUFFER_SIZE);
    bytes_read = read(sd, buffer, BUFFER_SIZE - 1);
    if (bytes_read < 0) {
        perror("read failed");
    } else if (bytes_read == 0) {
        printf("Server closed the connection.\n");
    } else {
        printf("Message received from server: '%s'\n", buffer);
    }

    close(sd);
    printf("Connection closed.\n");

    return 0;
}