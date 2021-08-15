#include <stdio.h>
#define length 8
typedef int  intV8 __attribute__ ((vector_size (length * sizeof(int))));

int main(int argc, const char *argv[])
{
  
  intV8 dataV1 = {1,2,3,4,5,6,7,8};
  intV8 dataV2 = {8,7,6,5,4,3,2,1};
  intV8 add = dataV1 + dataV2;
  intV8 mul = dataV1 * dataV2;
  intV8 dlv = dataV1 / dataV2;
  int i;
  for (i = 0; i < length; i++) {
    printf("%i ", add[i]);
  }

  putchar('\n');
  return 0;
}
