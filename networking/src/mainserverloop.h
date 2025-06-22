#ifndef MAIN_SERVER_LOOP_H
#define MAIN_SERVER_LOOP_H

#include "outh.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void server_loop(int socket_id);

int create_socket(const char *host, const char *port);

int point_to_dir_listen(int socket_id);
#endif // !MAIN_SERVER_LOOP_H
