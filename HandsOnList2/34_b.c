/*
=============================================================
Name        : 34_b.c
Author      : Rohitangshu Bose
Description : Write a program to create a concurrent server.
                b. Use pthread_create
Date        : 1st October, 2025.
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT_NO 8080
#define BUFFER_SIZE 1024

void *handle_client(void *socket_desc) {
    int nsfd = *(int *)socket_desc;
    free(socket_desc);  

    char buffer[BUFFER_SIZE] = {0};
    int read_size;

    while ((read_size = read(nsfd, buffer, sizeof(buffer))) > 0) {
        printf("Received from client: %s\n", buffer);

        const char *message = "Message From server\n";
        write(nsfd, message, strlen(message));

        memset(buffer, 0, BUFFER_SIZE); 
    }

    if (read_size == 0) {
        printf("Client disconnected.\n");
    } else if (read_size < 0) {
        perror("Read failed");
    }

    close(nsfd);
    return NULL;
}

int main() {
    struct sockaddr_in server, client;
    int sd, nsd, clientLen;

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; 
    server.sin_port = htons(PORT_NO);


    if (bind(sd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind failed");
        close(sd);
        exit(EXIT_FAILURE);
    }

    if (listen(sd, 5) < 0) {
        perror("Listen failed");
        close(sd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT_NO);

    while (true) {
        clientLen = sizeof(client);
        nsd = accept(sd, (struct sockaddr *)&client, (socklen_t *)&clientLen);
        if (nsd < 0) {
            perror("accept failed");
            continue; 
        }

        printf("Connected to client from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        int *new_socket = malloc(sizeof(int));
        if (new_socket == NULL) {
            perror("Could not allocate memory");
            close(nsd);
            continue;
        }
        *new_socket = nsd;

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, (void *)new_socket) != 0) {
            perror("Could not create thread");
            free(new_socket); 
            close(nsd);
        }
        pthread_detach(thread_id);
    }


    close(sd);
    return 0;
}

/*
================================================
Output:(Server)
________________________________________________
rohit2026~$gcc 34_b.c -o server.out
rohit2026~$./server.out 
Server listening on port 8080
Connected to client from 127.0.0.1:49792
Connected to client from 127.0.0.1:49793
Received from client: hi
Client disconnected.
Received from client: Hello
Client disconnected.
________________________________________________
Output:(Client1)
________________________________________________
rohit2026~$gcc 34_client.c -o client.out
rohit2026~$./client.out                 
Socket created successfully.
Connected to the server at 127.0.0.1:8080
Enter a message to send to the server: Hello
Message sent: 'Hello'
Message received from server: 'Message From server'
Connection closed.
________________________________________________
Output:(Client2)
________________________________________________
rohit2026~$./client.out                                             
Socket created successfully.
Connected to the server at 127.0.0.1:8080
Enter a message to send to the server: hi
Message sent: 'hi'
Message received from server: 'Message From server'
Connection closed.
================================================
*/