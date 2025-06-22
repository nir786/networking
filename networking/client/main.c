
#include "bindSocket.h"
#include "clientInput.h"
#include "reciveList.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  int socketfd = client_socket("127.0.0.1", "8001");

  printf("client started and is connected to the server\n");

  int list_filled = 0;
  int pasword_confirmed = 0;

  while (1) {
    if (pasword_confirmed == 0) {
      char buf[100];
      printf("enter something:\n");
      fgets(buf, sizeof(buf), stdin);
      char final_buf[113];
      snprintf(final_buf, sizeof(final_buf), "handshakeddd %s", buf);
      if (strstr(final_buf, "LEAVE") != NULL) {
        send(socketfd, final_buf, sizeof(final_buf), 0);
        close(socketfd);
        break;
      }
      send(socketfd, final_buf, sizeof(final_buf), 0);
      pasword_confirmed = 1;
    }

    if (list_filled == 0) {
      printf("client is ready to recive list\n");
      if (recive_list(socketfd) == 1)
        print_list();
      list_filled = 1;
    }
    if (send_picked_dir(socketfd) == 1)
      printf("dir picked secessfully\n");
    else
      printf("failed to pick dir\n");

    if (recive_list(socketfd) == 1)
      print_list();
  }

  return 0;
}
