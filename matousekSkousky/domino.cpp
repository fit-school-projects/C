#include <stdio.h>
#include <stdlib.h>

typedef struct Tdomino {
    int m_DominoCube[2];
    int m_Count;
} TDOMINO;

int cmpDominoBsearch(const void * a, const void * b)
{
    int * aPtr = (int*)a;
    TDOMINO * bPtr = (TDOMINO*)b;

    for (int i = 0; i < 2; i++){
        if (aPtr[i] > bPtr->m_DominoCube[i])
            return 1;
        else if (aPtr[i] < bPtr->m_DominoCube[i])
            return -1;
    }
    return 0;
}

int cmpDominoQsort(const void * a, const void * b)
{
    TDOMINO * aPtr = (TDOMINO*)a;
    TDOMINO * bPtr = (TDOMINO*)b;

    for (int i = 0; i < 2; i++){
        if (aPtr->m_DominoCube[i] > bPtr->m_DominoCube[i])
            return 1;
        else if (aPtr->m_DominoCube[i] < bPtr->m_DominoCube[i])
            return -1;
    }
    return 0;
}

int readInput(TDOMINO ** dominoCube, int * sizeDomino, int * maxSizeDomino, int * numOfDominos)
{
    int res;
    int domino[2];
    char bracket;
    
    while ( 1 ){
        if ( ( res = scanf(" [ %d | %d %c ", &domino[0], &domino[1], &bracket)) != 3
            || bracket != ']')
        return res == EOF ? EOF : 0;
        int found = 0;
        for (int i = 0; i < 2; i++){
            TDOMINO * findDomino = (TDOMINO*)bsearch(domino, *dominoCube, *sizeDomino, sizeof(TDOMINO), cmpDominoBsearch);
            if (findDomino){
                findDomino->m_Count += 1;
                found = 1;
                break;
            } else {
                int tmp = domino[0];
                domino[0] = domino[1];
                domino[1] = tmp; 
            }
        }
        if (!found){
            if (*sizeDomino >= *maxSizeDomino){
                *maxSizeDomino += *maxSizeDomino / 2 + 10;
                *dominoCube = (TDOMINO*) realloc (*dominoCube, *maxSizeDomino * sizeof(**dominoCube));
            }
            (*dominoCube)[*sizeDomino].m_Count = 1;
            for (int i = 0; i < 2; i++){
                (*dominoCube)[*sizeDomino].m_DominoCube[i] = domino[i];
            }
            (*sizeDomino)++;
            qsort(*dominoCube, *sizeDomino, sizeof(TDOMINO), cmpDominoQsort);
        }
        (*numOfDominos)++;
    }
    return 1;
}

void printOutput(TDOMINO * dominoCube, int sizeDomino, int numOfDominos)
{
    printf("Celkem kostek: %d\n", numOfDominos);
    for (int i = 0; i < sizeDomino; i++){
        if (dominoCube[i].m_DominoCube[0] > dominoCube[i].m_DominoCube[1]){
            printf("[%d|%d] %dx\n", dominoCube[i].m_DominoCube[1], dominoCube[i].m_DominoCube[0], dominoCube[i].m_Count);
        } else {
            printf("[%d|%d] %dx\n", dominoCube[i].m_DominoCube[0], dominoCube[i].m_DominoCube[1], dominoCube[i].m_Count);
        }
    }
}

int main ( void )
{
    int sizeDominoCube = 0, maxSizeDominoCube = 10;
    int numOfDominos = 0;
    TDOMINO * dominoCubes = (TDOMINO*) malloc (maxSizeDominoCube * sizeof(*dominoCubes));

    printf("Zadejte kostky:\n");
    if ( !readInput(&dominoCubes, &sizeDominoCube, &maxSizeDominoCube, &numOfDominos) || sizeDominoCube == 0){
        printf("Nespravny vstup.\n");
        free(dominoCubes);
        return 1;
    }

    printOutput(dominoCubes, sizeDominoCube, numOfDominos);
    free(dominoCubes);
    return 0;
}
