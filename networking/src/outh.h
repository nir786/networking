#ifndef OUTH_H
#define OUTH_H
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int confirm_packet_handshake(char *buf);

int confirm_pasword(int *fd);

void flush_all(int *fd);

#endif
