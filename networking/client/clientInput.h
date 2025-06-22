#ifndef CLIENT_INPUT_H
#define CLIENT_INPUT_H

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

int send_picked_dir(int);

#endif // ! CLIENT_INPUT_H
