#include "mainserverloop.h"
#include "outh.h"
#include "scan.h"
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

  int dir_pointer = 0;
  int password_confirmed = 0;
  /********LISTENING SOCKET********/
  int socketfd = create_socket(NULL, "8001");

  if (get_overview() == 1)
    print_list();

  int list_sent = 0;
  if (socketfd != -1) {
    printf("not socketfd");
  }

  while (1) {

    printf("server is listening.. \n");

    if (listen(socketfd, 10) == 1) {
      perror("listen ");
      exit(1);
    }

    struct sockaddr_storage their_addr;
    socklen_t add_size = sizeof(their_addr);
    int new_fd = accept(socketfd, (struct sockaddr *)&their_addr, &add_size);

    if (new_fd == -1) {
      perror("accept");
      continue;

    } else {
      while (1) {
        /****SERVER AUTHINTICATION*****/
        if (password_confirmed == 0) {
          printf("client connected\n");
          if (confirm_pasword(&new_fd) == 1) {
            /*****GET INPUT FROM CLIENT****/
            printf("server is ready to send list\n");

            if (list_sent == 0) {
              if (send_list(new_fd) == 1) {
                printf("list sent");
              }
              list_sent = 1;
            }
            password_confirmed = 1;
          }
        }
        dir_pointer = point_to_dir_listen(new_fd);
        printf("%d \n", dir_pointer);

        flush_all(&new_fd);
        get_dir_name(dir_pointer);
        printf("%s\n", dir_name);
        printf("%s\n", dogshit);
        make_new();
        send_list(new_fd);
      }
      /*******END CLIENT********/

      if (new_fd == -1)
        close(new_fd);

      printf("client terminated\n");
      /*************************/
    }
  }

  return 0;
}
