#include "outh.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int confirm_packet_handshake(char *buf) {

  if (strstr(buf, "handshakeddd") == NULL) {
    return 0;

  } else {

    return 1;
  }
}

int confirm_pasword(int *fd) {
  char password[255];

  int rec = recv(*fd, password, sizeof(password), 0);
  if (rec == -1) {
    flush_all(fd);
    return 0;
  } else {
    if (confirm_packet_handshake(password)) {
      if (strstr(password, "L@limtroll123") != NULL) {
        printf("password accepted\n");
        flush_all(fd);
        return 1;
      } else {
        flush_all(fd);
        return 0;
      }
    }
  }
  return 0;
}

void flush_all(int *fd) {
  char trash[255];
  while (recv(*fd, trash, sizeof(trash), MSG_DONTWAIT) > 0)
    ;
}
