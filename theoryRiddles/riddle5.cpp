#include <stdio.h>

int rec( int n, int * a, int * b)
{
    return n == 1 ? *a = *b : rec (n/2, b, a) + rec ((n+1)/2, a + n/2, b+n/2);
}

int main ( void )
{
    int a[] = {5,9,9,6,4,0};
    int b[] = {1,7,2,9,2,0};
    

    printf("%d %d\n", rec(5,a,b), rec(6,b,a));
    return 0;
}
