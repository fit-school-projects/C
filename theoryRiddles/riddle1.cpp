#include <stdio.h>


int main ( void )
{
    int i, count = 0;
    for (i = -511; i < 511; i++){
        if (i != -i)
            count++;
    }
    printf("%d\n", count);
    return 0;
}
