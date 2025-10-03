#include <stdio.h>
#include <string.h> 

int main ( void )
{
    char str[666];
    char * x = str + 4;
    strcpy ( str, "Hello world!" );
    while (*x ) {
        *x ++ = 0;
    }
    printf ("%s\n", str);
    return 0;
}
