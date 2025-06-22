#include "scan.h"
#include <dirent.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

char **list;
int scale;
char *dir_name;
char *dogshit;
int get_overview() {
  dogshit = malloc(255 * sizeof(char));
  strcpy(dogshit, "/home/nir");
  list = malloc(sizeof(char *) * 5);
  struct dirent *entry;
  DIR *dp = opendir("/home/nir/");
  if (dp == NULL) {
    return 0;
  }
  int size = 5;
  int count = 0;
  while ((entry = readdir(dp)) != NULL) {

    if (entry->d_name[0] != '.') {
      if (count < size) {
        sort_name(entry, count);
        count++;

      } else {
        size += size;
        list = realloc(list, size * sizeof(char *));

        sort_name(entry, count);
        count++;
      } // end else

    } // end big if
  } // endloop

  closedir(dp);

  scale = count;
  list = realloc(list, size * (sizeof(char *)));
  return 1;
}

void print_list() {

  for (int i = 0; i < scale; i++) {
    printf("%s\n", list[i]);
  }
}

void sort_name(struct dirent *entry, int count) {
  //[dir] [file];
  if (strstr(entry->d_name, ".") == NULL) {

    int size = strlen(entry->d_name) + 6;
    list[count] = malloc(size * sizeof(char));
    snprintf(list[count], size, "[DIR]%s", entry->d_name);
  } else {
    int size = strlen(entry->d_name) + 7;
    list[count] = malloc(size * sizeof(char));
    snprintf(list[count], size, "[FILE]%s", entry->d_name);
  }
}

int send_list(int socket_id) {

  /****send list size*****/
  uint8_t list_size = (uint8_t)scale;
  send(socket_id, &list_size, 1, 0);
  /*****confirmation*****/
  uint8_t confirm_1 = 0;
  if (recv(socket_id, &confirm_1, 1, 0) == 1) {
    if (confirm_1 != 1)
      return 0;
  } else
    return 0;
  //
  /****start sending names****/
  for (int i = 0; i < scale; i++) {
    uint8_t word_size = strlen(list[i]);
    uint8_t confirm_size;
    uint8_t confirm_word;
    /*******send word size******/
    send(socket_id, &word_size, 1, 0);
    /******client confirms words size****/
    if (recv(socket_id, &confirm_size, 1, 0) != 1) {
      printf("failed to send word %d\n", i);
      return 0;
    }
    /*****send word*******/
    send(socket_id, list[i], strlen(list[i]), 0);
    /**** confirm word***/
    if (recv(socket_id, &confirm_word, 1, 0) != 1)
      return 0;
    else if (confirm_word != 1)
      return 0;

  } // end loop

  return 1;
}

void get_dir_name(int dir_num) {
  //[dir]  Downloads
  dir_name = malloc(strlen(list[dir_num]) - 5);
  int count = 0;
  for (int i = 5; i < strlen(list[dir_num]); i++) {
    dir_name[count] = list[dir_num][i];
    count++;
  }
  dir_name[count] = '\0';
  char buffer[50];
  // printf("holyfuck");
  snprintf(buffer, sizeof(buffer), "%s/%s", dogshit, dir_name);
  // printf("bad realloc");
  dogshit = realloc(dogshit, strlen(buffer) * sizeof(char));
  strncpy(dogshit, buffer, strlen(buffer) * sizeof(char));
}

void free_list() {
  for (int i = 0; i < scale; i++) {
    free(list[i]);
  }
  free(list);
}

int make_new() {

  free_list();
  list = NULL;
  list = malloc(sizeof(char *) * 5);
  struct dirent *entry;

  DIR *dp = opendir(dogshit);
  if (dp == NULL) {
    return 0;
  }
  int size = 5;
  int count = 0;
  while ((entry = readdir(dp)) != NULL) {

    if (entry->d_name[0] != '.') {
      if (count < size) {
        sort_name(entry, count);
        count++;

      } else {
        size += size;
        list = realloc(list, size * sizeof(char *));

        sort_name(entry, count);
        count++;
      } // end else

    } // end big if
  } // endloop

  closedir(dp);

  scale = count;
  list = realloc(list, size * (sizeof(char *)));
  return 1;
}
