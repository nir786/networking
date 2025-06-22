#include "bindSocket.h"

int client_socket(const char *host, const char *port) {

  struct addrinfo hints;
  struct addrinfo *clientdata;

  memset(&hints, 0, sizeof hints);

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  int status = getaddrinfo(host, port, &hints, &clientdata);

  if (status != 0) {
    fprintf(stderr, "getaddrinfo : %s\n", gai_strerror(status));
    return 1;
  }

  struct addrinfo *p;
  int socketfd;
  for (p = clientdata; clientdata != NULL; clientdata = clientdata->ai_next) {

    socketfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

    if (socketfd == -1) {
      perror("socket");
      continue;
    }
    if (connect(socketfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(socketfd);
      perror("connect");
    }

    break;
  }

  return socketfd;
}
