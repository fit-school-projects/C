#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main( void )
{
    srand (time(NULL));
    for (int i = 0; i < 10000; i++)
        printf("# %d %d\n", rand() % 100000, rand() % 4000000 + 100000);
    return 0;
}