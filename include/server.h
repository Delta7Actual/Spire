#ifndef SERVER_H
#define SERVER_H

#include <stddef.h>
#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>

typedef struct s_conn {
    int server_sock;
    int client_sock;
} Conn;

int open_conn(uint16_t port);
Conn *connect_conn(int server_sock);
int close_conn(Conn *conn);

#endif