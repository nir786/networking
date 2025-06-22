#include "reciveList.h"
#include <stdint.h>
#include <sys/socket.h>

char **List;
int size;
int recive_list(int socket_id) {

  uint8_t list_size;
  uint8_t false = 0;
  uint8_t true = 1;

  if (recv(socket_id, &list_size, 1, 0) != 1) {
    send(socket_id, &false, 1, 0);
    return 0;
  } else
    List = malloc(((int)list_size) * sizeof(char *));
  send(socket_id, &true, 1, 0);

  for (int i = 0; i < ((int)list_size); i++) {

    uint8_t word_size;
    if (recv(socket_id, &word_size, 1, 0) != 1) {
      send(socket_id, &false, 1, 0);
      return 0;
    } else
      send(socket_id, &true, 1, 0);

    List[i] = malloc(((int)word_size) * sizeof(char));
    if (recv(socket_id, List[i], ((int)word_size), 0) != word_size) {
      send(socket_id, &false, 1, 0);
      return 0;
    } else
      send(socket_id, &true, 1, 0);
  }

  size = (int)list_size;

  return 1;
}

void print_list() {
  for (int i = 0; i < size; i++) {
    printf("%s\n", List[i]);
  }
}
