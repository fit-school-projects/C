#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void fibonacci(int n)
{
    int * cache = (int*) malloc ((n+1) * sizeof(*cache));
    cache[0] = 0;
    cache[1] = 1;
    for ( int i = 2; i <= n; i++ ){
        cache[i] = cache[i-1] + cache[i-2];
    }
    for ( int i = 0; i <= n; i++ ){
        printf("%d. clen: %d\n", i, cache[i]);
    }
    
}

void test(int a, int b)
{
    do {
        a+=1;
    } while (a != 100);

    while (b !=100)
    { 
        b+=1;
    }
    printf("%d,%d\n", a,b);
}

int main ()
{
    //fibonacci(25);
    test(0,0);
    return 0;
}
