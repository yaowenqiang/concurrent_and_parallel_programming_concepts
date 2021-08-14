#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include "utils.h"

#define MAX_BUFFERS (BACKLOG + 1)

int main() {
  char buffer[BUFF_SIZE + 1];
  struct sockaddr_in client_addr;
  socklen_t len = sizeof(struct sockaddr_in);
  int sock = create_server_socket(true);
  struct epoll_event event, event_buffers[MAX_BUFFERS];
  int epollfd = epoll_create1(0);
  if (epollfd < 0) {
    error_msg("Problem with epoll_create", true);
  }

  event.events = EPOLLIN;
  event.data.fd = sock;
  if(epoll_ctl(epollfd, EPOLL_CTL_ADD, sock, &event) < 0) {
    error_msg("Problem with epoll_ctl call", true);
  }

  while(true) {
    int n = epoll_wait(epollfd, event_buffers, MAX_BUFFERS, -1);
    if (n < 0) {
      error_msg("Problem with epoll_wait call", true);
    }
    int i;
    for(i = 0; i < n;i++) {
      if(event_buffers[i].data.fd == sock) {
        while(true) {
          socklen_t len = sizeof(client_addr);
          int client = accept(sock, (struct sockaddr *) &client_addr, &len);
          if (client < 0 && (EAGAIN == errno || EWOULDBLOCK == errno)) {
            break;
          }
          fcntl(client, F_SETFL, O_NONBLOCK);
          event.events = EPOLLIN;
          event.data.fd = client;
          if (epoll_ctl(epollfd, EPOLL_CTL_ADD, client, &event) < 0) {
            error_msg("Problem with epoll_ctl ADD call", false);
            announce_client(&client_addr.sin_addr);
          }
        }
      } else {
        bzero(buffer, sizeof(buffer));
        int bytes_read = recv(event_buffers[i].data.fd,buffer, sizeof(buffer), 0);
        if (bytes_read > 0) {
          char response[BUFF_SIZE * 2];
          bzero(response, sizeof(response));
          generate_echo_response(buffer, response);
          int bytes_written = send(event_buffers[i].data.fd, response, strlen(response), 0);
          if (bytes_written < 0) {
            error_msg("Problem with read call", false); 
            close(event_buffers[i].data.fd);
          }

        }
      }
    }
  }
  return 0;
}


