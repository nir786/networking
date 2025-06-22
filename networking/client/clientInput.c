#include "clientInput.h"
#include <stdint.h>
#include <sys/socket.h>

int send_picked_dir(int socket_id) {

  char handshake[] = "handshakeddd";
  uint8_t confirm_handshake;

  send(socket_id, handshake, sizeof(handshake), 0);
  if (recv(socket_id, &confirm_handshake, 1, 0) <= 0)
    return -1;

  if (confirm_handshake == 0)
    return -1;

  char buf[10];
  fgets(buf, sizeof(buf), stdin);
  int number = atoi(buf);

  uint8_t confirm_input;
  uint8_t send_number = (uint8_t)number;
  send(socket_id, &send_number, 1, 0);
  if (recv(socket_id, &confirm_input, 1, 0) <= 0)
    return -1;
  if (confirm_input == 0)
    return -1;

  return 1;
}
