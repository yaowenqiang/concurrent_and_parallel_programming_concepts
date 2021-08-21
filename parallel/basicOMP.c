#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main() {
  int t_count = 0, tid;

#pragma omp parallel private(t_count, tid)
  {
    tid = omp_get_thread_num();
    printf("Thread %i\n", tid);

    if (tid == 0) {
      t_count = omp_get_num_threads();
      printf("Thread count on this machine is %i\n\n", t_count);
    }
  }

  puts("Goodbye, cruel world!");
}
