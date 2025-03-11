#include "../include/server.h"

int open_conn(uint16_t port) {
    if (port <= 5000) return -1;

    struct sockaddr_in client_addr = {0}, server_addr = {0};
    int *server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) return -1;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock, (struct sock_addr *) &server_addr, sizeof(server_addr)) < 0) {
        close(server_sock);
        return -1;
    }

    listen(*server_sock, 1);
    int *client_sock = accept(server_sock, (struct sock_addr *) &client_addr, sizeof(client_addr));
    if (*client_sock < 0) {
        close(server_sock);
        return -1;
    }

    return 0;
}

int close_conn(int server_sock, int client_sock) {
    close(server_sock);
    close(client_sock);
    return 0;
}