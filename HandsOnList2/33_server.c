/*
============================================================================
Name        : 33_server.c
Author      : Rohitangshu Bose
Description : Write a program to communicate between two machines using socket.
Date        : 1st October, 2025.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT_NO 8080
#define BUFFER_SIZE 1024

int main() {
    int sd, nsd;
    struct sockaddr_in serv, cli;
    socklen_t cli_len;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT_NO);

    if (bind(sd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("bind failed");
        close(sd);
        exit(EXIT_FAILURE);
    }

    if (listen(sd, 5) < 0) {
        perror("listen failed");
        close(sd);
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT_NO);

    cli_len = sizeof(cli);
    nsd = accept(sd, (struct sockaddr *)&cli, &cli_len);
    if (nsd < 0) {
        perror("accept failed");
        close(sd);
        exit(EXIT_FAILURE);
    }
    printf("Connection accepted from a client.\n");

    memset(buffer, 0, BUFFER_SIZE);
    bytes_read = read(nsd, buffer, BUFFER_SIZE - 1);
    if (bytes_read > 0) {
        printf("Received from client: '%s'\n", buffer);
        write(nsd, buffer, bytes_read);
        printf("Echoed message back to client.\n");
    }

    close(nsd);
    close(sd);
    printf("Server shutting down.\n");

    return 0;
}

/*
================================================
Output:
________________________________________________
rohit2026~$gcc 33_server.c -o server.out
rohit2026~$./server.out                 
Server listening on port 8080...
Connection accepted from a client.
Received from client: 'Hello'
Echoed message back to client.
Server shutting down.
================================================
*/