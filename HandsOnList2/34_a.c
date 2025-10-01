/*
=============================================================
Name        : 34_a.c
Author      : Rohitangshu Bose
Description : Write a program to create a concurrent server.
                b. Use fork()
Date        : 1st October, 2025.
=============================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT_NO 8080
#define BUFFER_SIZE 1024

void process_client_request(int client_sock, struct sockaddr_in client_details);

int main() {
    int listen_sock_fd, client_conn_fd;
    struct sockaddr_in host_addr, peer_addr;
    socklen_t peer_addr_size;

    listen_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock_fd == -1) {
        perror("Could not create listening socket");
        exit(EXIT_FAILURE);
    }

    memset(&host_addr, 0, sizeof(host_addr));
    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT_NO);
    host_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_sock_fd, (struct sockaddr *)&host_addr, sizeof(host_addr)) < 0) {
        perror("Could not bind socket to address");
        close(listen_sock_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(listen_sock_fd, 5) < 0) {
        perror("Could not set socket to listen");
        close(listen_sock_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server awaiting connections on port %d\n", PORT_NO);

    while (1) {
        peer_addr_size = sizeof(peer_addr);
        client_conn_fd = accept(listen_sock_fd, (struct sockaddr *)&peer_addr, &peer_addr_size);
        if (client_conn_fd < 0) {
            perror("Failed to accept incoming connection");
            continue;
        }

        pid_t child_pid = fork();

        if (child_pid < 0) {
            perror("Failed to fork new process");
            close(client_conn_fd);
        } 
        else if (child_pid == 0) {

            close(listen_sock_fd); 
            process_client_request(client_conn_fd, peer_addr);
            exit(EXIT_SUCCESS);
        } 
        else {

            close(client_conn_fd); 
        }
    }

    close(listen_sock_fd);
    return 0;
}

void process_client_request(int client_sock, struct sockaddr_in client_details) {
    char data_buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    printf("Child process handling client from %s:%d\n",
           inet_ntoa(client_details.sin_addr), ntohs(client_details.sin_port));

    memset(data_buffer, 0, sizeof(data_buffer));
    bytes_received = read(client_sock, data_buffer, sizeof(data_buffer) - 1);

    if (bytes_received < 0) {
        perror("Failed to read from client");
    } else if (bytes_received > 0) {
        printf("Client sent: \"%s\"\n", data_buffer);
        const char *response = "Server acknowledges your message.";
        if (write(client_sock, response, strlen(response)) < 0) {
            perror("Failed to write response to client");
        }
    }

    close(client_sock);
}
/*
================================================
Output:(Server)
________________________________________________
rohit2026~$gcc 34_a.c -o server.out
rohit2026~$./server.out            
Server awaiting connections on port 8080
Child process handling client from 127.0.0.1:49808
Child process handling client from 127.0.0.1:49809
Client sent: "Hello!!!!!"
Client sent: "Hi there!"
^C
________________________________________________
Output:(Client1)
________________________________________________
rohit2026~$./client.out
Socket created successfully.
Connected to the server at 127.0.0.1:8080
Enter a message to send to the server: Hi there!
Message sent: 'Hi there!'
Message received from server: 'Server acknowledges your message.'
Connection closed.
________________________________________________
Output:(Client2)
________________________________________________
rohit2026~$./client.out                                             
Socket created successfully.
Connected to the server at 127.0.0.1:8080
Enter a message to send to the server: Hello!!!!!
Message sent: 'Hello!!!!!'
Message received from server: 'Server acknowledges your message.'
Connection closed.
================================================
*/