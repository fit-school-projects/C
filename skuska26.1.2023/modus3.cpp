#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ADDRESS 11
typedef struct TAddress
{
    char    m_Street[MAX_ADDRESS];
    int     m_Salary;
} TADDRESS;

typedef struct TSalaries {
    int m_Salary;
    int m_Count;
} TSALARY;

int cmpInt(const void * a, const void * b)
{
    int aPtr = *(const int*)a;
    TSALARY * bPtr = (TSALARY*)b;

    if (aPtr < bPtr->m_Salary)
        return -1;
    else if (aPtr > bPtr->m_Salary)
        return 1;
    return 0;
}

int cmpIntQsort(const void * a, const void * b)
{
    TSALARY * aPtr = (TSALARY*)a;
    TSALARY * bPtr = (TSALARY*)b;

    if (aPtr->m_Salary < bPtr->m_Salary)
        return -1;
    else if (aPtr->m_Salary > bPtr->m_Salary)
        return 1;
    return 0;
}

int cmpCountQsort(const void * a, const void * b)
{
    TSALARY * aPtr = (TSALARY*)a;
    TSALARY * bPtr = (TSALARY*)b;

    if (aPtr->m_Count < bPtr->m_Count)
        return 1;
    else if (aPtr->m_Count > bPtr->m_Count)
        return -1;
    return 0;
}

void addAddress(TADDRESS ** address, int * sizeAddress, int * maxSizeAddress, char * street, int salary)
{
    if (*sizeAddress >= *maxSizeAddress)
    {
        *maxSizeAddress += *maxSizeAddress / 2 + 10;
        *address = (TADDRESS *) realloc (*address, *maxSizeAddress * sizeof ( **address ) );
    }
    TADDRESS element;
    element.m_Salary = salary;
    strcpy(element.m_Street, street);
    (*address)[(*sizeAddress)++] = element;
}

void findSalary(int salary, TSALARY * salaries, int * countSalaries)
{
    TSALARY * foundSalary = (TSALARY*)bsearch(&salary, salaries, *countSalaries, sizeof(TSALARY), cmpInt);
    if (foundSalary){
        foundSalary->m_Count += 1;
    } else {
        salaries[*countSalaries].m_Salary = salary;
        salaries[*countSalaries].m_Count = 1;
        (*countSalaries)++;
        qsort(salaries, *countSalaries, sizeof(TSALARY), cmpIntQsort);
    }

//    int found = 0;
//    for (int i = 0; i < *countSalaries; i++){
//        if (salaries[i].m_Salary == salary){
//            salaries[i].m_Count += 1;
//            found = 1;
//            break;
//        }
//    }
//    if (!found){
//        salaries[*countSalaries].m_Salary = salary;
//        salaries[*countSalaries].m_Count = 1;
//        (*countSalaries)++;
//    }

}

void findModus(TADDRESS * address, int sizeAddress, char * street)
{
    TSALARY salaries[1000];
    int countSalaries = 0;
    if (street[0] == '*'){
        for (int i = 0; i < sizeAddress; i++){
            findSalary(address[i].m_Salary, salaries, &countSalaries);
        }
    } else {
        for (int i = 0; i < sizeAddress; i++){
            if (strncmp(address[i].m_Street, street, strlen(street)) == 0){
                findSalary(address[i].m_Salary, salaries, &countSalaries);
            }
        }
    }
  
    if (countSalaries == 0){
        printf("Modus: N/A\n");
        return;
    }
    qsort(salaries, countSalaries, sizeof(TSALARY), cmpCountQsort);
    int maxCount = salaries[0].m_Count;
    printf("Modus:");
    for (int i = 1; i < countSalaries; i++){
        if (salaries[i].m_Count == maxCount)
            printf(" %d,", salaries[i].m_Salary);
    }
    printf(" %d [%d]\n", salaries[0].m_Salary, maxCount);
}

int validateStreet(char * street)
{
//    if (strlen(street) > MAX_ADDRESS - 1)
//        return 0;
    if (street[0] == '*')
        return 1;
    for (int i = 0; i < (int) strlen(street); i++){
        if (street[i] < '0' || street[i] > '9')
            return 0;
    }
    return 1;
}

int readInput(TADDRESS ** address, int * sizeAddress, int * maxSizeAddress)
{
    char    street[MAX_ADDRESS];
    int     salary, res;
    char    mark;
    int     wasQuestion = 0;

    while ( 1 )
    {
        if ( ( res = scanf(" %c", &mark)) != 1 )
            return res == EOF ? EOF : 0;
        switch ( mark )
        {
            case '+':
                if(wasQuestion)
                    return 0;
                if ( scanf(" %10s %d", street, &salary) != 2 || !validateStreet(street) || salary < 0)
                    return 0;
                addAddress(address, sizeAddress, maxSizeAddress, street, salary);
                break;
            case '?':
                wasQuestion = 1;
                if ( scanf(" %10s", street) != 1 || !validateStreet(street))
                    return 0;
                findModus(*address, *sizeAddress, street);
                break;
            default:
                return 0;
        }
    }
    return 0;
}

int main ( void )
{
    int sizeAddress = 0, maxSizeAddress = 10;
    TADDRESS * address = (TADDRESS *) malloc ( maxSizeAddress * sizeof ( TADDRESS ) );

    if ( !readInput(&address, &sizeAddress, &maxSizeAddress)){
        free(address);
        printf("Nespravny vstup.\n");
        return 1;
    }
    free(address);
    return 0;
}
