#include <stdio.h>
#include <xmmintrin.h>
#include <stdint.h>

typedef void (*func) ();
#define length (2048)
#define AlignedVals (4)

float v1[length]  __attribute__ ((aligned(16)));
float v2[length]  __attribute__ ((aligned(16)));
float v3[length]  __attribute__ ((aligned(16)));
float r1[length]  __attribute__ ((aligned(16)));
float r2[length]  __attribute__ ((aligned(16)));

void init() {
  unsigned i;
  for (i = 0; i < length; i++) {
    v1[i] = (float) (rand() / RAND_MAX); 
    v2[i] = (float) (rand() / RAND_MAX); 
    v3[i] = (float) (rand() / RAND_MAX); 
  }
}

void in_serial() {
  unsigned i;
  for (int i = 0; i < length; i++) {
    r1[i] = (v1[i] + v2[i])*v3[i];
  }
}

void in_parallel() {
  __m128* mm_v1 = (__m128*) v1;
  __m128* mm_v2 = (__m128*) v2;
  __m128* mm_v3 = (__m128*) v3;
  __m128* mm_rv = (__m128*) r2;
  unsigned i;
  unsigned n = length / AlignedVals;
  for(i = 0; i < n; i++) {
    mm_rv[i] = _mm_mul_ps(_mm_add_ps(mm_v1[i], mm_v2[i]), mm_v3[i]);
  }
}

uint64_t rdtsc() {
  uint32_t lo, hi;
  __asm__ __volatile__ (
    "xorl %%eax, %%eax\n"
      "cpuid\n"
      "rdtsc\n"
      : "=a" (lo), "=d" (hi)
      :
      : "%ebx", "%ecx"
  );
  return (uint64_t) hi << 32 | lo;
}

void time_it(const char* msg, func func2run) {
  unsigned long long start, stop;
  start = rdtsc();
  func2run();
  stop = rdtsc();
  printf("%s: %lld\n", msg, stop - start);
}

int main() {
  init();
  time_it("in_serial() ", in_serial);
  time_it("in_parallel() ", in_parallel);
  return 0;
}
