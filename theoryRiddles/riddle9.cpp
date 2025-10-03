#include <stdio.h>
#include <stdlib.h>

int count;

int foo(int * p, int n)
{
    int a[94];
    count++;
    int i;
    for (i = 0; i < n; i++)
        a[i] = p[i];
    if (n == 1){
        return a[0];
    } 
    if (foo(a, n-1) > a[n-1])
        return foo(a, n-1);
    else
        return a[n-1];
}

int main ()
{
    int b[94], i;
    for (i = 0; i < 94; i++)
        b[i] = rand();
    foo(b, 94); 
    printf("%d\n", count);

    return 0;
}
