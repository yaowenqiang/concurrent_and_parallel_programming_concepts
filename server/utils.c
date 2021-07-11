#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include "utils.h"

void error_msg(const char* msg, bool halt_flag)
{
  perror(msg);
  if (halt_flag) {
    exit(-1);
  }
}

int create_server_socket(bool non_blocking)
{
  const int port = 3000;
  struct sockaddr_in server_addr;
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (socket < 0) {
    error_msg("Problem with socket call", true);
  }

  if (non_blocking) {
    fcntl(sock, F_SETFL, O_NONBLOCK);
  }

  /* bind */
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port); /* host to network endian */

  if (bind(sock, (struct sockaddr*) & server_addr, sizeof(server_addr)) < 0) {
    error_msg("Problem with bind call", true);
  }
  fprintf(stderr, "Listening for requests on port %d...\n", port);
  if (listen(sock, BACKLOG) < 0) {
    error_msg("Problem with listen call", true);
  }
  return sock;
}

void announce_client(struct in_addr* addr) {
  char buffer[BUFF_SIZE + 1];
  inet_ntop(AF_INET, addr, buffer, sizeof(buffer));
  fprintf(stderr, "Client connected from %s...\n", buffer);
}

void generate_echo_response(char request[], char response[]) {
  strcpy(response, "HTTP/1.1 200 OK\n");
  strcpy(response, "Content-Type: text/*\n");
  strcpy(response, "Accept-Ranges: bytes\n");
  strcpy(response, "Connection: close\n\n");
  strcpy(response, request);
}
