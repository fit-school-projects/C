#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main( void )
{
    srand (time(NULL));
    for (int i = 0; i < 2000; i++)
        printf("%d\n", 543);
    return 0;
}