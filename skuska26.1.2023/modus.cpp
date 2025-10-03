#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_REG 11
typedef struct TSalary {
    int m_Salary;
    int m_Count;
} TSALARY;

typedef struct TRegions {
    char region[MAX_REG];
    TSALARY m_Salaries[10000];
    int m_CountSalary;
} TREG;

int cmpSalaryBsearch(const void * a, const void * b)
{
    int aPtr = *(const int*)a;
    TSALARY * bPtr = (TSALARY*)b;

    if (aPtr < bPtr->m_Salary)
        return 1;
    else if (aPtr > bPtr->m_Salary)
        return -1;
    return 0;
}

int cmpSalariesQsort(const void * a, const void * b)
{
    TSALARY * aPtr = (TSALARY*)a;
    TSALARY * bPtr = (TSALARY*)b;

    if (aPtr->m_Salary < bPtr->m_Salary)
        return 1;
    else if (aPtr->m_Salary > bPtr->m_Salary)
        return -1;
    return 0;
}

int cmpCountOfSalaries(const void * a, const void * b)
{
    TSALARY * aPtr = (TSALARY*)a;
    TSALARY * bPtr = (TSALARY*)b;

    if (aPtr->m_Count < bPtr->m_Count)
        return 1;
    else if (aPtr->m_Count > bPtr->m_Count)
        return -1;
    return 0;
}

int cmpRegionsQsort(const void * a, const void * b)
{
    TREG * aPtr = (TREG*)a;
    TREG * bPtr = (TREG*)b;

    return strcmp(aPtr->region, bPtr->region);
}

int cmpRegionsBsearch(const void * a, const void * b)
{
    char * aPtr = (char*)a;
    TREG * bPtr = (TREG*)b;

    return strcmp(aPtr, bPtr->region);
}

void addPartOfCode(TREG ** regions, int * sizeRegions, int * maxSizeRegions, char * newCode, int salary)
{
    if (*sizeRegions >= *maxSizeRegions){
        *maxSizeRegions += *maxSizeRegions / 2 + 10;
        *regions = (TREG*) realloc (*regions, *maxSizeRegions * sizeof(**regions));
    }
    TREG * foundRegion = (TREG*)bsearch(newCode, *regions, *sizeRegions, sizeof(TREG), cmpRegionsBsearch);
    if (foundRegion){
        TSALARY * foundSalary = (TSALARY*)bsearch(&salary, foundRegion->m_Salaries, foundRegion->m_CountSalary, sizeof(TSALARY), cmpSalaryBsearch);
        if (foundSalary){
            foundSalary->m_Count += 1;
        } else {
            foundRegion->m_Salaries[foundRegion->m_CountSalary].m_Salary = salary;
            foundRegion->m_Salaries[foundRegion->m_CountSalary].m_Count = 1;
            foundRegion->m_CountSalary++;
            qsort(foundRegion->m_Salaries, foundRegion->m_CountSalary, sizeof(TSALARY), cmpSalariesQsort);
        }
    } else {
        strcpy((*regions)[*sizeRegions].region, newCode);
        (*regions)[*sizeRegions].m_Salaries[0].m_Salary = salary;
        (*regions)[*sizeRegions].m_Salaries[0].m_Count = 1;
        (*regions)[*sizeRegions].m_CountSalary++;
        (*sizeRegions)++;
        qsort(*regions, *sizeRegions, sizeof(TREG), cmpRegionsQsort);
    }
}

int addRegion(TREG ** regions, int * sizeRegions, int * maxSizeRegions)
{
    int salary;
    char code[MAX_REG];
    if ( scanf(" %s %d", code, &salary) != 2 || salary < 0){
        return 0;
    }
    // ** ALL REGIONS ** //
    TSALARY * foundSalary = (TSALARY*)bsearch(&salary, (*regions)[0].m_Salaries, (*regions)[0].m_CountSalary, sizeof(TSALARY), cmpSalaryBsearch);
    if (foundSalary){
        foundSalary->m_Count += 1;
    } else {
        (*regions)[0].m_Salaries[(*regions)[0].m_CountSalary].m_Salary = salary;
        (*regions)[0].m_Salaries[(*regions)[0].m_CountSalary].m_Count = 1;
        (*regions)[0].m_CountSalary += 1;
        qsort((*regions)[0].m_Salaries, (*regions)[0].m_CountSalary, sizeof(TSALARY), cmpSalariesQsort);
    }
    // ** add all variations of codes ** //
    int i = 0;
    char newCode[MAX_REG] = { };
    while (code[i] != '\0'){
        if (!isdigit(code[i]))
            return 0;
        newCode[i] = code[i];
        i++;
        addPartOfCode(regions, sizeRegions, maxSizeRegions, newCode, salary);
    }
    return 1; 
}
int validateCode(char * code)
{
    int pos = 0;
    if (code[pos] == '*' && strlen(code) == 1)
        return 1;
    while (code[pos] != '\0')
    {
        if (!isdigit(code[pos]))
            return 0;
        pos++;
    }
    return 1;
}
int readInput(TREG ** regions, int * sizeRegions, int * maxSizeRegions )
{
    int wasQuestion = 0;
    while ( 1 )
    {
        char mark;
        int res;
        if ( ( res = scanf(" %c", &mark)) != 1 ){
            return res == EOF ? EOF : 0;
        }
        switch (mark)
        {
        case '+':
            if ( !addRegion(regions, sizeRegions, maxSizeRegions) || wasQuestion)
                return 0;
            break;
        case '?':
            wasQuestion = 1;
            char code[MAX_REG]; 
            if ( scanf("%s", code) != 1 || !validateCode(code)){
                return 0;
            }
            if (code[0] == '*'){
                qsort((*regions)[0].m_Salaries, (*regions)[0].m_CountSalary, sizeof(TSALARY), cmpCountOfSalaries);
                int max = (*regions)[0].m_Salaries[0].m_Count;
                printf("Modus:");
                for (int i = 1; i < (*regions)[0].m_CountSalary; i++){
                    if ((*regions)[0].m_Salaries[i].m_Count == max){
                        printf(" %d,", (*regions)[0].m_Salaries[i].m_Salary);
                    }
                }
                printf(" %d [%d]\n", (*regions)[0].m_Salaries[0].m_Salary, max);
            } else {
                TREG * foundRegion = (TREG*)bsearch(code, *regions, *sizeRegions, sizeof(TREG), cmpRegionsBsearch);
                if (foundRegion){
                    qsort(foundRegion->m_Salaries, foundRegion->m_CountSalary, sizeof(TSALARY), cmpCountOfSalaries);
                    int max = foundRegion->m_Salaries[0].m_Count;
                    printf("Modus:");
                    for (int i = 1; i < foundRegion->m_CountSalary; i++){
                        if (foundRegion->m_Salaries[i].m_Count == max){
                            printf(" %d,", foundRegion->m_Salaries[i].m_Salary);
                        }
                    }
                    printf(" %d [%d]\n", foundRegion->m_Salaries[0].m_Salary, max);
                } else {
                    printf("Modus: N/A.\n");
                }
            }
            break;
        default:
            return 0;
            break;
        }
    }
}

int main ( void )
{
    int sizeRegions = 0, maxSizeRegions = 10;
    TREG * regions = (TREG*) malloc (maxSizeRegions * sizeof(*regions));
    strcpy(regions[0].region, "*");
    sizeRegions++;

    printf("Data:\n");
    if ( !readInput(&regions, &sizeRegions, &maxSizeRegions) || sizeRegions == 0){
        printf("Nespravny vstup.\n");
        free(regions);
        return 1;
    } 

    free(regions);    
    return 0;
}
