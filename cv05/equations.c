#include <stdio.h>
#include <math.h>

void comparison(double res, double c)
{
    if (fabs(res - c) <= 1000 * __DBL_EPSILON__ * fabs(c)) {
        printf("Rovnice je spravne.\n");
    } else {
        printf("%g != %g\n", res, c);
    }
}

int main ( void )
{
    double a, b, c, res;
    char op;
    printf("Zadejte rovnici:\n");
    if ( scanf(" %lf %c %lf = %lf", &a, &op, &b, &c) != 4 ) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    switch ( op )
    {
    case '+':
        res = a + b;
        comparison(res, c);
        break;
    case '-':
        res = a - b;
        comparison(res, c);
        break;
    case '*':
        res = a * b;
        comparison(res, c);
        break;
    case '/':
        if (b == 0) {
            printf ("Nespravny vstup.\n");
            return 1;
        }
        res = trunc(a / b);
        comparison(res, c);
        break;
    
    default:
        printf ("Nespravny vstup.\n");
        return 1;
        break;
    }

    return 0;
}