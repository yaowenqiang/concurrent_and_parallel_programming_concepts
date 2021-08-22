#include <stdio.h>
#include <omp.h>

static float balance = 0.0f;

int main() {
  const int how_many = 8000000;
  unsigned i;

#pragma omp parallel for
  for (i = 0; i < how_many; i++) {
    #pragma omp atomic
    balance++;
    #pragma omp atomic
    balance--;
  }
  printf("After %i deposits and %i withdrawals, the balance is : %f.\n", how_many, how_many, balance);
  return 0;

}
