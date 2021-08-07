#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>

#define MaxEvents 12
#define MaxReads 12000

unsigned is_prime(unsigned n) {
  if (n <= 3) {
    return n > 1;
  }
  if (0 == (n % 2) ||  0 == (n % 3)) {
    return 0;
  }
  unsigned i;
  for(i = 5; (i * i) <=n; i+= 6) {
    if(0 == (n % i ) || 0 == (n % (i + 2))) {
      return 0;
    }
  }
  printf("%i is prime.\n", n);
  return 1;
}

void report_and_die(const char* msg) {
  perror(msg);
  exit(-1);
}

int create_nonblocking(const char* name) {
  int fd = open(name, O_RDONLY);
  if (fd < 0) {
    return fd;
  }

  int flag = fcntl(fd, F_SETFL, O_NONBLOCK);
  if (flag < 0) {
    return flag;
  }
  return fd;
}

int main() {
  const char* file = "./pipe1";
  int fd = create_nonblocking(file);
  if (fd < 0) {
    report_and_die("create_nonblocking(file)");
  }

  int epollFD = epoll_create1(0);
  if (epollFD < 0) {
    report_and_die("epoll_create1(0)");
  }

  struct epoll_event toKernel;
  struct epoll_event fromKernel[MaxEvents];
  toKernel.events = EPOLLIN;
  toKernel.data.fd = fd;
  if(epoll_ctl(epollFD, EPOLL_CTL_ADD, fd, &toKernel) < 0) {
    report_and_die("epoll_ctl(...)");
  }
  unsigned howmany = 0;
  int count = 0;
  while(count++ < MaxReads) {
    int n = epoll_wait(epollFD, fromKernel, MaxEvents, -1);
    if (n < 0) {
      report_and_die("epoll_wait(...)");
    }
    int i;
    for(i = 0;i < n; i++) {
      int next = 0;
       int bytes_read = read(fromKernel[i].data.fd, &next, sizeof(int));
       if (sizeof(int) == bytes_read) {
         if(is_prime(next)) {
           howmany++;
         }
       }
    }

    close(fd);
    close(epollFD);
    unlink(file);


    printf("\n%u primes were found among the %i values read.\n", howmany, MaxReads);
    return 0;
  }

}
