#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TNames {
    char * m_Name;
    int    m_Count;
} TNAME; 

// bserach porovnavam string a hladam v strukture, preto sa to lisi od cmpNamesQsort
int cmpNamesBsearch( const void * a, const void *b)
{
    char * aPtr = (char*)a;
    TNAME * bPtr = (TNAME*)b;

    return strcmp(aPtr, bPtr->m_Name);
}

int cmpNamesQsort( const void * a, const void *b)
{
    TNAME * aPtr = (TNAME*)a;
    TNAME * bPtr = (TNAME*)b;

    return strcmp(aPtr->m_Name, bPtr->m_Name);
}

int cmpInt(const void * a, const void * b)
{
    TNAME * aPtr = (TNAME*)a;
    TNAME * bPtr = (TNAME*)b;
    if (aPtr->m_Count > bPtr->m_Count)
        return -1;
    else if (aPtr->m_Count < bPtr->m_Count)
        return 1;
    return 0; 
}

int readInput(TNAME ** names, int * sizeName, int * maxSizeNames)
{
    char * line = NULL;
    size_t capacity = 0;
    while (getline(&line, &capacity, stdin) != -1)
    {
        char * tmp = line;
        int offset = 0;
        char * name = (char*) malloc (strlen(line) * sizeof(char));
        while (sscanf(tmp, " %s%n", name, &offset) == 1){
            tmp += offset;
            
            char * tmpName = (char*) malloc (strlen(line) * sizeof(char));
            if (sscanf(tmp, " %s", tmpName) != 1){
                free(name);
                free(tmpName);
                break;
            }
            free(tmpName);
            TNAME * foundName = (TNAME*)bsearch(name, *names, *sizeName, sizeof(TNAME), cmpNamesBsearch);
            if (foundName){
                foundName->m_Count++;
            } else {
                if (*sizeName >= *maxSizeNames){
                    *maxSizeNames += *maxSizeNames / 2 + 10;
                    *names = (TNAME*) realloc (*names, *maxSizeNames * sizeof(**names));
                }
                (*names)[*sizeName].m_Name = name;
                (*names)[*sizeName].m_Count = 1;
                (*sizeName)++;
                qsort(*names, *sizeName, sizeof(TNAME), cmpNamesQsort);
            }
            name = (char*)malloc(strlen(line) * sizeof(char));
        }
    }
    free(line);
    return 1;
}

void freeNames(TNAME * names, int size)
{
    for (int i = 0; i < size; i++){
        free(names[i].m_Name);
    }
    free(names);
}
int main ( void )
{
    int sizeNames = 0, maxSizeNames = 10;
    TNAME * names = (TNAME *) malloc (maxSizeNames * sizeof(*names));

    printf("Mena:\n");
    if ( !readInput(&names, &sizeNames, &maxSizeNames)){
        printf("Nespravny vstup.\n");
        freeNames(names, sizeNames);
        return 1;
    }
    qsort(names, sizeNames, sizeof(TNAME), cmpInt);
    int max = names[0].m_Count;
    printf("Celkom: %dx\n", max);
    for (int i = 0; i < sizeNames; i++){
        if (names[i].m_Count == max){
            printf("%s\n", names[i].m_Name);
        }
    }

    freeNames(names, sizeNames);
    return 0;
}


