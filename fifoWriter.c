#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MaxWrites 256

int main()
{
  srand(time(0));
  const char* fifoName = "./myPipe1";
  mkfifo(fifoName, 0666);
  int fd = open(fifoName, O_CREAT | O_WRONLY);
  int i;
  for (i = 0; i < MaxWrites; i++) {
    int n = rand();
    write(fd, &n, sizeof(int));
  }

  close(fd);
  //unlink(fifoName);
  return 0;
}
