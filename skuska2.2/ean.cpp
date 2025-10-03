#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Tean {
    char m_Ean[101];
    int  m_Count;
} TEAN;

int cmpCodesBsearch(const void * a, const void * b)
{
    char * aPtr = (char*)a;
    TEAN * bPtr = (TEAN*)b;

    return strcmp(aPtr, bPtr->m_Ean);
}

int cmpCodesQsort(const void * a, const void * b)
{
    TEAN * aPtr = (TEAN*)a;
    TEAN * bPtr = (TEAN*)b;

    return strcmp(aPtr->m_Ean, bPtr->m_Ean);
}

int validateCode(char * code)
{
    if (strlen(code) < 5 || strlen(code) > 100){
        return 0;
    }
    for (int i = 0; i < strlen(code); i++){
        if (!isdigit(code[i])){
            return 0;
        }
    }
    return 1;
}

void addCode(TEAN ** eanCodes, int * sizeCode, int * maxSizeCode, int count, char * code)
{
    TEAN * foundCode = (TEAN*)bsearch(code, *eanCodes, *sizeCode, sizeof(TEAN), cmpCodesBsearch);
    if (foundCode){
        foundCode->m_Count += count;
        printf("%dx\n", foundCode->m_Count);
    } else {
        if (*sizeCode >= *maxSizeCode){
            *maxSizeCode += *maxSizeCode / 2 + 10;
            *eanCodes = (TEAN*) realloc (*eanCodes, *maxSizeCode * sizeof(**eanCodes));
        }
        strcpy((*eanCodes)[*sizeCode].m_Ean, code);
        (*eanCodes)[*sizeCode].m_Count = count;
        printf("%dx\n", (*eanCodes)[*sizeCode].m_Count);
        (*sizeCode)++;
        qsort(*eanCodes, *sizeCode, sizeof(TEAN), cmpCodesQsort);
    }
}

void removeCode(TEAN ** eanCodes, int * sizeCode, int * maxSizeCode, int count, char * code)
{
    TEAN * foundCode = (TEAN*)bsearch(code, *eanCodes, *sizeCode, sizeof(TEAN), cmpCodesBsearch);
    if (foundCode){
        if (foundCode->m_Count < count){
            printf("Nedostatek zbozi.\n");
        } else {
            foundCode->m_Count -= count;
            printf("%dx\n", foundCode->m_Count);
        }
    } else {
        printf("Nedostatek zbozi.\n");
    }
}

int readInput(TEAN ** eanCode, int * sizeCode, int * maxSizeCode)
{
    while ( 1 )
    {
        char code[102];
        char mark;
        int count;
        int res;
        if ( ( res = scanf("%c %dx %101s", &mark, &count, code)) != 3 || count < 0)
            return res == EOF ? EOF : 0; 
        
        if (!validateCode(code)){
            return 0;
        }
        switch (mark)
        {
        case '+':
            addCode(eanCode, sizeCode, maxSizeCode, count, code);
            break;
         case '-':
            removeCode(eanCode, sizeCode, maxSizeCode, count, code);
            break;
        
        default:
            return 0;
        }
    }
    return 1;
}

int main ( void )
{
    int sizeCode = 0, maxSizeCode = 10;
    TEAN * eanCode = (TEAN *) malloc (maxSizeCode * sizeof(*eanCode));
    if ( !readInput(&eanCode, &sizeCode, &maxSizeCode)){
        free(eanCode);
        printf("Nespravny vstup.\n");
        return 1;
    }

    free(eanCode);
    return 0;
}
