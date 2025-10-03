#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define VALUE_LIMIT 1000000

int readInput(int * intervals, int * count)
{
    int a,b,res;
    char bracket;
    while ( 1 )
    {
        if ( ( res = scanf(" [ %d , %d %c", &a, &b, &bracket)) != 3 )
            return res == EOF ? EOF : 0;
        for (int i = a; i < b; i++){
            intervals[i] += 1;
            if (intervals[i] == 1){
                (*count)++;
            }
        }
    }
    return 1;
}

int main() {
    int intervals[VALUE_LIMIT] = { };
    int count = 0;
   
    printf("Zadejte intervaly:\n");
    if ( !readInput(intervals, &count)){
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Celkova delka intervalu: %d\n", count);
    return 0;
}
