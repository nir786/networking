#ifndef RECIVE_LIST_H
#define RECIVE_LIST_H

#include <arpa/inet.h>
#include <dirent.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
extern int size;
extern char **list;
int recive_list(int);
void print_list();
#endif // !RECIVE_LIST_H#include <unistd.h>
