#include <stdio.h>

#define length 8

int main()
{
  int array1[] = {1,2,3,4,5,6,7,8};
  int array2[] = {8,7,6,5,4,3,2,1};
  int sum[length];

  int i;
  for (i = 0; i < length; i++) {
    sum[i] = array1[i] + array2[i];
  }
  for( i = 0; i < length; i++) {
    printf("%i ", sum[i]);
  }

  putchar('\n');
  return 0;
}
