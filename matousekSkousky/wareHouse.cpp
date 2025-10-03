#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    FALSE = 0,
    TRUE = 1
} BOOLEAN;

typedef struct Tcodes {
    char * m_Code;
    int m_Count;
} TCODES;

int cmpCodeBsearch(const void * a, const void * b)
{
    char * aPtr = (char*)a;
    TCODES * bPtr = (TCODES*)b;

    return strcmp(aPtr, bPtr->m_Code);
}

int cmpCodeQsort(const void * a, const void * b)
{
    TCODES * aPtr = (TCODES*)a;
    TCODES * bPtr = (TCODES*)b;

    return strcmp(aPtr->m_Code, bPtr->m_Code);
}

void addCode(TCODES ** codes, int * sizeCodes, int * maxSizeCodes, char * code, int count)
{
    TCODES * findCode = (TCODES*)bsearch(code, *codes, *sizeCodes, sizeof(TCODES), cmpCodeBsearch);
    if (findCode){
        findCode->m_Count += count;
        printf("Pridano.\n");
        free(code);
    } else {
        if (*sizeCodes >= *maxSizeCodes){
            *maxSizeCodes += *maxSizeCodes / 2 + 10;
            *codes = (TCODES*) realloc (*codes, *maxSizeCodes * sizeof(**codes));
        }
        (*codes)[*sizeCodes].m_Code = code;
        (*codes)[*sizeCodes].m_Count = count;
        (*sizeCodes)++;
        printf("Vytvoreno.\n");
        qsort(*codes, *sizeCodes, sizeof(TCODES), cmpCodeQsort);
    }
}

void removeCode(TCODES ** codes, int * sizeCodes, char * code, int count)
{
    TCODES * findCode = (TCODES*)bsearch(code, *codes, *sizeCodes, sizeof(TCODES), cmpCodeBsearch);
    if (findCode){
        if (findCode->m_Count < count){
            printf("Nedostatek zbozi.\n");
        } else {
            findCode->m_Count -= count;
            printf("Odebrano.\n");
        }
    }
    free(code);
}

void askAmount(TCODES ** codes, int * sizeCodes, char * code)
{
    TCODES * findCode = (TCODES*)bsearch(code, *codes, *sizeCodes, sizeof(TCODES), cmpCodeBsearch);
    if (findCode){
        printf("Kusu: %d.\n", findCode->m_Count);
    }
    free(code);
}

int readInput(TCODES ** codes, int * sizeCodes, int * maxSizeCodes)
{
    char * line = NULL;
    size_t capacity = 0;

    while ( getline(&line, &capacity, stdin) != -1 )
    {
        char mark;
        char * code = (char*) malloc (strlen(line) * sizeof(char));  
        int count, offset;
       
        sscanf (line, " %c%n", &mark, &offset);
        char * tmpLine = line + offset;
        switch (mark)
        {
        case '+':
            if ( sscanf(tmpLine, "%s %d", code, &count) != 2){
                return FALSE;
            }
            addCode(codes, sizeCodes, maxSizeCodes, code, count);
            break;
        case '-':
            if ( sscanf(tmpLine, "%s %d", code, &count) != 2){
                return FALSE;
            }
            removeCode(codes, sizeCodes, code, count);
            break;
        case '?':
            if ( sscanf(tmpLine, "%s", code) != 1){
                return FALSE;
            }
            askAmount(codes, sizeCodes, code);
            break;
        default:
            free(line);
            return FALSE;
        }
    }
    free(line);
    return TRUE;
}

void freeCodes(TCODES * codes, int sizeCodes)
{
    for (int i = 0; i < sizeCodes; i++){
        free(codes[i].m_Code);
    }
    free(codes);
}

int main ( void )
{
    int sizeCodes = 0, maxSizeCodes = 10;
    TCODES * codes = (TCODES*) malloc (maxSizeCodes * sizeof(*codes));

    printf("Prikazy:\n");
    if ( !readInput(&codes, &sizeCodes, &maxSizeCodes)){
        printf("Nespravny vstup.\n");
        freeCodes(codes, sizeCodes);;
        return TRUE;
    }

    freeCodes(codes, sizeCodes);
    return FALSE;
}
