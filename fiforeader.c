#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
  const char* fifoName = "./myPipe1";
  int num;
  int fd = open(fifoName, O_RDONLY);
  while(read(fd, &num, sizeof(num)) > 0) {
    printf("%d\n", num);
  }

  close(fd);
  unlink(fifoName);
  return 0;
}

