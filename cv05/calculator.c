#include <stdio.h>
#include <math.h>

int main ( void )
{
    double a, b;
    char op, equalSign;
    printf("Zadejte vzorec:\n");
    if ( scanf (" %lf %c %lf %c", &a, &op, &b, &equalSign ) != 4 
        || equalSign != '=')
    {
        printf ("Nespravny vstup.\n");
        return 1;
    }

    switch ( op )
    {
    case '+':
        printf("%g\n", a + b);
        break;
    case '-':
        printf("%g\n", a - b);
        break;
    case '*':
        printf("%g\n", a * b);
        break;
    case '/':
        if (b == 0) {
            printf ("Nespravny vstup.\n");
            return 1;
        }
        printf("%g\n", trunc(a / b));
        break;
    
    default:
        printf ("Nespravny vstup.\n");
        return 1;
        break;
    }

    return 0;
}