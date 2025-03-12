#include "../include/server.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int open_conn(uint16_t port) {
    if (port <= 5000) return -1;

    struct sockaddr_in server_addr = {0};

    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) return -1;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        close(server_sock);
        return -1;
    }

    listen(server_sock, 1);
    return server_sock;
}

Conn *connect_conn(int server_sock) {
    if (server_sock < 0) {
        fprintf(stderr, "Invalid server socket.\n");
        return NULL;
    }

    struct sockaddr_in client_addr = {0};
    socklen_t client_len = sizeof(client_addr);

    int client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
    if (client_sock < 0) {
        return NULL;
    }

    Conn *conn = malloc(sizeof(Conn));
    if (!conn) {
        close(client_sock);
        return NULL;
    }

    conn->server_sock = server_sock;
    conn->client_sock = client_sock;

    printf("Client connected. Client socket: %d\n", client_sock);
    return conn;
}
int close_conn(Conn *conn) {
    if (!conn) return -1;
    close(conn->server_sock);
    close(conn->client_sock);
    free(conn);
    return 0;
}