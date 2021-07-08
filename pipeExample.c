#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ReadEnd 0
#define WriteEnd 1

void report_and_die(const char* msg) {
  perror(msg);
  exit(-1);
}

int main()
{
  int pipePDs[2];
  char buf;
  const char* msg = "this is the winter of our discontent\n";
  if (pipe(pipePDs) < 0) {
    report_and_die("pipe(...)");
  }

  pid_t cpid = fork();
  if (cpid < 0) {
    report_and_die("fork()");
  }

  /*** child ***/
  if (0 == cpid) {
    close(pipePDs[WriteEnd]);

    while (read(pipePDs[ReadEnd], &buf, 1) > 0) {
      write(STDOUT_FILENO, &buf, sizeof(buf)) ;
    }
    close(pipePDs[ReadEnd]);
    _exit(0);
  } else {
    close(pipePDs[ReadEnd]);
    write(pipePDs[WriteEnd], msg, strlen(msg));
    close(pipePDs[WriteEnd]);
    wait(0);
    exit(0);
  }


  return 0;
}
