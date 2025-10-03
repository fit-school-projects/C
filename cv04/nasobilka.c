#include <stdio.h>

int spaces(int range)
{
    int spaces, count = 0;
    spaces = range * range;
    while ( spaces != 0 )
    {
        spaces = spaces / 10;
        count++;
    }
    return count + 1;
}

int main ( void )
{
    int range;
    printf("Rozsah:\n");
    if ( scanf(" %d", &range) != 1 
        || range <= 0 )
    {
        printf ("Nespravny vstup.\n");
        return 1;
    }

    //first line
    int n = range;
    printf("%*c", spaces(range), '|');
    for ( int i = 0; i < range; i++ )
    {
        printf( "%*d", spaces(range), n );
        n--;
    } 
    printf("\n");
    
    //dividing line
    for (int i = 1; i < spaces(range); i++)
        printf("%c", '-');
    printf("%c", '+');
    for (int i = 0; i < range * spaces(range); i++)
        printf("%c", '-');
    printf("\n");

    // pyramide
    int tmp = range;
    for ( int i = 1; i <= range; i++ )
    {
        int tmp2 = range;
        printf("%*d|", spaces(range)-1, i);
        for (int j = 0; j < tmp; j++)
        {
            printf("%*d", spaces(range), i * tmp2);
            tmp2--;
        }
        printf("\n");
        tmp--;
    }

    return 0;
}