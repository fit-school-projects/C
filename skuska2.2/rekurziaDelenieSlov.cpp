#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Twords {
    char code[101];
    int * space;
    int length;
    int count;
} TWORD;

int readInput(TWORD * c)
{
    if ( scanf("%101s", c->code) != 1 || strlen(c->code) > 100 ){
        return 0;
    } 
    c->length = strlen(c->code);
    return 1;
}

void getlineRec(TWORD * c, int idx, int space)
{
    c->space[idx] = space;
    if (idx == c->length-1){
        for (int i = 0; i < c->length; i++){
            if (c->space[i] == 1){
                printf(" ");
            }
            printf("%c", c->code[i]);   
        }
        printf("\n");
        return;
    }

    getlineRec(c, idx + 1, 0);
    if (!space){
        getlineRec(c, idx + 1, 1);
    }
}

int main ( void )
{
    TWORD c = {};
    if ( !readInput(&c)){
        printf("Nepsravny vstup.\n");
        return 1;
    }
    c.space = (int*) calloc (c.length, sizeof(int));

    getlineRec(&c, 0, 0);
    free(c.space);
    return 0;
}
