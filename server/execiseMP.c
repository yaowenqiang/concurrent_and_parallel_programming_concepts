#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main() {
  signal(SIGCHLD, SIG_IGN);
  int n = 777;
  printf("Initial value:  %i\n", n);
  pid_t pid = fork();
  if (-1 == pid) {
    perror("fork() error");
    exit(0);
  }
  if (0 == pid ) {
    n = n + 10;
    printf("Add 10          %i\n", n);
  } else {
    n = n - 10;
    printf("Sub 10          %i\n", n);
  }
  return 0;
}
