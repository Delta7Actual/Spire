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

int open_conn(uint16_t port);
int close_conn(int conn);

#endif