#include "mainserverloop.h"
#include "outh.h"
#include <stdint.h>
#include <sys/socket.h>

void server_loop(int socket_id) {

  while (1 && socket_id != -1) {
    char buf[113];
    int num_bytes = recv(socket_id, buf, sizeof(buf) - 1, 0);

    if (num_bytes == -1) {
      perror("recv");
      continue;
    }

    if (confirm_packet_handshake(buf) == 0) {
      printf("%s \n", buf);
      close(socket_id);

      break;
    }

    if (strstr(buf, "LEAVE") != NULL) {
      printf("client disconnecting\n");
      close(socket_id);
      printf("client disconnected\n");

      break;
    }
    char peek[1];
    int result = recv(socket_id, peek, 1, MSG_PEEK | MSG_DONTWAIT);

    printf("server recived: %s\n ", buf);
    if (result > 0)
      flush_all(&socket_id);
    else
      break;
  }
}

int point_to_dir_listen(int socket_id) {

  char buf[20];
  uint8_t true = 1;
  uint8_t false = 0;

  if (recv(socket_id, buf, sizeof(buf), 0) > 0) {
    send(socket_id, &true, 1, 0);
  } else {
    send(socket_id, &false, 1, 0);
    return -1;
  }
  if (confirm_packet_handshake(buf) == 0)
    return -1;
  uint8_t picked_number;
  if (recv(socket_id, &picked_number, 1, 0) <= 0) {
    send(socket_id, &false, 1, 0);
    return -1;
  }

  send(socket_id, &true, 1, 0);

  return (int)picked_number;
}

int create_socket(const char *host, const char *port) {

  struct addrinfo hints;
  struct addrinfo *servinfo;

  memset(&hints, 0, sizeof hints);

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  int status = getaddrinfo(host, port, &hints, &servinfo);

  if (status != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    return 1;
  }

  int socketfd;
  struct addrinfo *p;
  for (p = servinfo; p != NULL; p = p->ai_next) {

    socketfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (socketfd == -1) {
      perror("socket");
      continue;
    }

    if (bind(socketfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(socketfd);
      perror("bind");
      continue;
    }

    break;
  }

  return socketfd;
}
