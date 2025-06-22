#ifndef SCAN_H
#define SCAN_H

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
extern char **list;
extern int scale;
extern char *dir_name;
extern char *dogshit;
void print_list();

int get_overview();

void sort_name(struct dirent *entry, int count);

int send_list(int);

void get_dir_name(int dir_num);

void add_to_path();

int make_new();

void free_list();
#endif // !SCAN_H
