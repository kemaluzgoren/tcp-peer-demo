/**
 * @file      main.c 
 * 
 * @author    Kemal UZGOREN
 * 
 * @version   v1.0.0
 * @date      25.05.2025
 * @details   
 */

 #include "client.h"
 #include "server.h"
 
 #include <string.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <stdio.h>
 #include <arpa/inet.h>
 #include <pthread.h>
 
 #define PORT            8080
 #define BUFFER_SIZE     1024
 

 static void run_server(void);
 static void run_client(const char *server_ip);
 
 int main(int argc, char *argv[])
 {
    if (argc < 2) {
        printf("Usage:\n");
        printf("  Server: %s server\n", argv[0]);
        printf("  Client: %s client <server_ip>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "server") == 0) {
        run_server();
    } else if (strcmp(argv[1], "client") == 0 && argc >= 3) {
        run_client(argv[2]);
    } else {
        fprintf(stderr, "Invalid parameters.\n");
        return EXIT_FAILURE;
    }

     return 0;
 }
 

 static void run_server(void) {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("[SERVER] Listening on port %d...\n", PORT);

    while (1) {
        addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        memset(buffer, 0, BUFFER_SIZE);
        read(client_socket, buffer, BUFFER_SIZE);
        printf("[SERVER] Message received: %s\n", buffer);

        // Send a reply
        const char *reply = "Server received the message.";
        write(client_socket, reply, strlen(reply));

        close(client_socket);
    }

    close(server_socket);
}


static void run_client(const char *server_ip) {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("> Enter message: ");
        fflush(stdout);

        if (!fgets(buffer, BUFFER_SIZE, stdin)) continue;

        buffer[strcspn(buffer, "\n")] = '\0';
        if (strcmp(buffer, "exit") == 0) break;

        write(client_socket, buffer, strlen(buffer));

        // Read reply
        char reply[BUFFER_SIZE] = {0};
        read(client_socket, reply, BUFFER_SIZE);
        printf("[CLIENT] Reply from server: %s\n", reply);
    }

    close(client_socket);
}
