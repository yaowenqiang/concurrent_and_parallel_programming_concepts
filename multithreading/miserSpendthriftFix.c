#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

static int balance = 0;
static pthread_mutex_t lock;


void report_and_die(const char* msg) {
  perror(msg);
  exit(0);
}

void* deposit(void* n) {
  int* ptr = (int*)n;
  //int limit = *ptr, i;
  int limit = *ptr;
  for (int i = 0; i < limit; i++) {
    if(pthread_mutex_lock(&lock) == 0) {
        balance++;
        pthread_mutex_unlock(&lock);
    } else {
      report_and_die("pthread_mutext_lock ( deposit)");
    }

  }
  return 0;
}

void* withdraw(void* n) {
  int* ptr = (int*) n;
  int limit = *ptr, i;
  for (i = 0; i  < limit; i++) {
    if(pthread_mutex_lock(&lock) == 0) {
      balance--;
    } else {
      report_and_die("pthread_mutext_lock ( withdraw)");
    }
  }
  return 0;
}

int main(int argc, char* argv[]) {
  /*
  if (argc < 2) {
    fprintf(stderr , "Usage: miserSpendshift <number of operation apiece>\n");
    return 0;
  }
  */

  //int n = atoi(argv[1]);
  int n = 1;

  pthread_t miser, spendthrift;
  pthread_mutex_init(&lock, 0);

  if (pthread_create(&miser, 0, deposit, &n) < 0) {
    report_and_die("pthread_create: miser");
  }

 
  if (pthread_create(&spendthrift, 0, withdraw, &n) < 0) {
    report_and_die("pthread_create: spendthrift");
  } 

  pthread_join(miser,0);
  pthread_join(spendthrift, 0);
  pthread_mutex_destroy(&lock);

  printf("The final balance is: %16i\n", balance);
  return 0;
}

