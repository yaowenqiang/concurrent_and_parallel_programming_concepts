#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char* const args[] = {"./fileStatus", "tmp", 0};
  int ret = execv("./filestatus", args);
  if (-1 == ret) {
    perror("execv(...) error");
    exit(-1);
  } else {
    //won't be executed, the current process is replaced by the exec process
    printf("I'm here\n");
  }
}
