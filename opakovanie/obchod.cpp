#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct TPriceList {
    char m_Code[102];
    int  m_Price;
} TPRICELIST;

int cmpCode(const void * a, const void * b)
{
    TPRICELIST * aPtr = (TPRICELIST*)a;
    TPRICELIST * bPtr = (TPRICELIST*)b;

    return strcmp(aPtr->m_Code, bPtr->m_Code); 
}

int cmpCodesBsearch(const void * a, const void * b)
{
    char * aPtr = (char*)a;
    TPRICELIST * bPtr = (TPRICELIST*)b;

    return strcmp(aPtr, bPtr->m_Code); 
}

int validateCode(char * code)
{
    for (int i = 0; i < strlen(code); i++){
        if(!isdigit(code[i])){
            return 0;
        }
    }
    return 1;
}

int readPriceList(TPRICELIST ** codes, int * sizeCodes, int * maxSizeCodes)
{
    while ( 1 )
    {
        int price;
        char code[102];
        char * line = NULL;
        size_t capacity = 0;
        if ( getline(&line, &capacity, stdin) == -1){
            free(line);
            return 0;
        }
        if (line[0] == '\n'){
            qsort(*codes, *sizeCodes, sizeof(TPRICELIST), cmpCode);
            free(line);
            return 1;
        }
        if ( sscanf(line, " %101s => %d", code, &price) != 2 || !validateCode(code) || strlen(code) > 100 || price <= 0)
            return 0;
        if (*sizeCodes >= *maxSizeCodes){
            *maxSizeCodes += *maxSizeCodes / 2 + 10;
            *codes = (TPRICELIST*) realloc (*codes, *maxSizeCodes * sizeof(**codes));
        }
        strcpy((*codes)[*sizeCodes].m_Code, code);
        (*codes)[*sizeCodes].m_Price = price;
        (*sizeCodes)++;
    }
    return 1;
}
int readBills(TPRICELIST * codes, int sizeCodes)
{
    int sum = 0;
    printf("Ucet:\n");
    
    while ( 1 ){
        char * line = NULL;
        size_t capacity = 0;

        if ( getline(&line, &capacity, stdin) == -1){
            printf("Celkem: %d\n", sum);
            free(line);
            return 1;
        }
            
        if (line[0] == '\n'){
            printf("Celkem: %d\n", sum);
            sum = 0;
            printf("Ucet:\n");
            continue;
        }
        char code[102];
        if ( sscanf(line, "%101s", code ) != 1 || strlen(code) > 100 || !validateCode(code)){
            free(line);
            return 0;
        }
            
        TPRICELIST * foundCode = (TPRICELIST*)bsearch(code, codes, sizeCodes, sizeof(TPRICELIST), cmpCodesBsearch);
        if (foundCode){
            sum += foundCode->m_Price;
        } else {
            free(line);
            return 0;
        }
    } 
    return 1;
}

int main ( void )
{
    int sizeCodes = 0, maxSizeCodes = 10;
    TPRICELIST * codes = (TPRICELIST*) malloc (maxSizeCodes * sizeof(*codes));

    printf("Cennik:\n");
    if ( !readPriceList(&codes, &sizeCodes, &maxSizeCodes) ){
        printf("Nespravny vstup.\n");
        free(codes);
        return 1;
    }
    if ( !readBills(codes, sizeCodes) ){
        printf("Nespravny vstup.\n");
        free(codes);
        return 1;
    }

    free(codes);
    return 0;
}
