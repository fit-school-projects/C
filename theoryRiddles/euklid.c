#include <stdio.h>

int euklidAlgortihm(int u, int v)
{
    while ( v != 0){
        int t = v;
        v = u % v;
        u = t;
    }
    return u;
}

int main ()
{
    printf("The greatest common divisor is: %d\n", euklidAlgortihm(762, 31));
    return 0;
}
