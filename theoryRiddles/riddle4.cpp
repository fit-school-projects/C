#include <stdio.h>
#include <limits.h>

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

int main()
{
  int a = 5, b = 3;
  printf("%d %d\n", MIN(a++,b++), a);
  return 0;
}
