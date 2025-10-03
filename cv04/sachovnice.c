#include <stdio.h>

void dividingLine (int fieldCount, int fieldSize)
{
    printf("+");
    for (int i = 0; i < (fieldCount * fieldSize); i++ )
        printf("%c", '-');
    printf("+\n");
}

void spaceFirstLine(int fieldCount, int fieldSize)
{
    printf("|");
    for (int j = 0; j < fieldCount; j++)
    {
        if( (j%2) == 0 )
        {
            for (int k = 0; k < fieldSize; k++)
                printf(" ");
        } else {
            for (int k = 0; k < fieldSize; k++)
                printf("X");
        }
    }
    printf("|\n");
}
void exFirstLine(int fieldCount, int fieldSize)
{
    printf("|");
    for (int j = 0; j < fieldCount; j++)
    {
        if( (j%2) == 0 )
        {
            for (int k = 0; k < fieldSize; k++)
                printf("X");
        } else {
            for (int k = 0; k < fieldSize; k++)
                printf(" ");
        }
    }
    printf("|\n");
}

int main ( void )
{
    int fieldCount, fieldSize;
    printf("Zadejte pocet poli:\n");
    if ( scanf("%d", &fieldCount) != 1 || fieldCount <= 0 )
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    printf("Zadejte velikost pole:\n");
    if ( scanf("%d", &fieldSize) != 1 || fieldSize <= 0 )
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    
    dividingLine(fieldCount, fieldSize);

    for (int i = 0; i < (fieldCount*fieldSize); i++)
    {
        if (((i / fieldSize) % 2) == 0)
        {
            spaceFirstLine(fieldCount, fieldSize);
        } else {
            exFirstLine(fieldCount, fieldSize);
        }
    }
    dividingLine(fieldCount, fieldSize);
    
    return 0;
}