#ifndef BIND_SOCKET_H
#define BIND_SOCKET_H

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int client_socket(const char *, const char *);

#endif // !DEBUG
