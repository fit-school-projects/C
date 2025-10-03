#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Tregals {
    int  m_RegalID;
    char * m_Product;
} TREG;

typedef struct TshoppingList
{
   int  m_Position;
   int  m_PosInList;
   int  m_exactMatch;
   char * m_Product;
   char * m_RegalProduct;
} TLIST;

/**
 * @brief function which strips the line feed at the end of the string
 * 
 * @param line 
 */
void stripLF (char * line)
{
    int length = strlen(line);
    if (length > 0 && line[length-1] == '\n')
        line[length-1] = '\0';
}

/* COMPARE FUNCTIONS for qsort and bsearch */
int cmpList(const void * a, const void * b)
{
    TLIST * aPtr = (TLIST*)a;
    TLIST * bPtr = (TLIST*)b;

    if(aPtr->m_Position > bPtr->m_Position)
        return 1;
    else if(aPtr->m_Position < bPtr->m_Position)
        return -1;
    if(aPtr->m_PosInList > bPtr->m_PosInList)
        return 1;
    else if(aPtr->m_PosInList < bPtr->m_PosInList)
        return -1;
    return 0;
}

int cmpStr(TREG * a, TREG * b)
{
    return strcasecmp(a->m_Product, b->m_Product);
}

int cmpStr2(char * a, TREG * b)
{
    return strcasecmp(a, b->m_Product);
}

/**
 * @brief function which reads the products from the regals and saves them into the structure Tregals
 * 
 * @param regals 
 * @param regalsSize 
 * @param regalsMaxSize 
 * @param numOfRegals
 * @return int 
 */
int readRegals(TREG ** regals, int * regalsSize, int * regalsMaxSize, int * numOfRegals)
{
    int currentRegal = -1;
    char * product = NULL;
    size_t capacity = 0;
    
    while ( getline(&product, &capacity, stdin) != -1 ){
        if (product[0] == '\n') {
            free(product);
            return 1;
        }
        if (product[0] == '#'){
            if (sscanf(product, "#%d", numOfRegals) != 1 || *numOfRegals != currentRegal + 1){
                free(product);
                return 0;
            }
            currentRegal++;
        } else {
            if (currentRegal == -1){
                free(product);
                return 0;
            } 
            if (*regalsSize >= *regalsMaxSize)
            {
                *regalsMaxSize += *regalsMaxSize / 2 + 10;
                *regals = (TREG*) realloc (*regals, *regalsMaxSize * sizeof(**regals) );
            }
            (*regals)[*regalsSize].m_RegalID = *numOfRegals;
            stripLF(product);
            (*regals)[*regalsSize].m_Product = (char*)malloc((capacity+1) * sizeof(char));
            strcpy((*regals)[*regalsSize].m_Product, product);
            (*regalsSize)++;
        }
        
    }
    if (feof(stdin)){
        free(product);
        return 0;
    }
    return 1;
}
/**
 * @brief function which reads the current shopping cart and saves it into the structure TshoppingList
 * 
 * @param shoppingList 
 * @param shoppingListSize 
 * @param shoppingListMaxSize 
 * @param numOfRegals 
 * @return int // 1 for LF and -1 for EOF
 */
int readShoppingList(TLIST ** shoppingList, int * shoppingListSize, int * shoppingListMaxSize, int numOfRegals)
{
    char * product = NULL;
    size_t capacity = 0;
    * shoppingList = (TLIST*) malloc (*shoppingListMaxSize * sizeof(**shoppingList));

    while ( getline(&product, &capacity, stdin) != -1 ){
        if (product[0] == '\n') {
            free(product);
            return 1;
        }
        if (*shoppingListSize >= *shoppingListMaxSize)
        {
            *shoppingListMaxSize += *shoppingListMaxSize / 2 + 10;
            *shoppingList = (TLIST*) realloc (*shoppingList, *shoppingListMaxSize * sizeof(**shoppingList) );
        }
        (*shoppingList)[*shoppingListSize].m_Position = numOfRegals + 1;
        (*shoppingList)[*shoppingListSize].m_exactMatch = 0;
        stripLF(product);
        (*shoppingList)[*shoppingListSize].m_PosInList = * shoppingListSize;
        (*shoppingList)[*shoppingListSize].m_Product = (char*)malloc((capacity+1)*sizeof(char));
        strcpy((*shoppingList)[*shoppingListSize].m_Product, product);
        (*shoppingListSize)++;
    }
    if (feof(stdin)) {
        free(product);
        return -1;
    }
    return 1;
}
/**
 * @brief function which finds the product from the shopping list in the current regal and optimalize the shopping list of the products according 
 * to the position in the regals
 * using bsearch function to quickly find the exactMatch, if there is not an exactMatch we are searching for the potential substring of the product in regals
 * 
 * @param shoppingList 
 * @param regalsList 
 * @param regalsSorted 
 * @param regalsSize 
 * @param shoppingListSize 
 * @param numOfRegals 
 */
void optimalizeList(TLIST ** shoppingList, TREG ** regalsList, TREG ** regalsSorted, int * regalsSize, int * shoppingListSize, int numOfRegals)
{    
    for (int i = 0; i < *shoppingListSize; i++){
        TREG * tmp = (TREG *)bsearch((*shoppingList)[i].m_Product, *regalsSorted, *regalsSize, sizeof(**regalsSorted),(int(*)(const void *, const void *))cmpStr2);
        if (!tmp){
            for (int j = 0; j < *regalsSize; j++)
            {
                if ((*shoppingList)[i].m_Position == (numOfRegals + 1) && (*shoppingList)[i].m_exactMatch == 0 && strcasestr((*regalsList)[j].m_Product, (*shoppingList)[i].m_Product)){
                    (*shoppingList)[i].m_Position = (*regalsList)[j].m_RegalID;
                    (*shoppingList)[i].m_RegalProduct = (*regalsList)[j].m_Product;
                    break;
                }
            }
        } else {
            (*shoppingList)[i].m_Position = tmp->m_RegalID;
            (*shoppingList)[i].m_RegalProduct = tmp->m_Product;
            (*shoppingList)[i].m_exactMatch = 1;
        }
    }
    qsort(*shoppingList, *shoppingListSize, sizeof(**shoppingList), cmpList);
}

void printOptimalizedList(TLIST ** shoppingList, int * shoppingListSize, int numOfRegals)
{
    printf("Optimalizovany seznam:\n");
    int count = 0;
    for (int i = 0; i < *shoppingListSize; i++){
        if ((*shoppingList)[i].m_Position != numOfRegals + 1){
            printf(" %d. %s -> #%d %s\n", count, (*shoppingList)[i].m_Product, (*shoppingList)[i].m_Position, (*shoppingList)[i].m_RegalProduct);
            count++;
        }
        else {
            printf(" %d. %s -> N/A\n", count, (*shoppingList)[i].m_Product);
            count++;
        }
    }
}

void freeRegals(TREG ** regals, int * regalsSize)
{
    for (int i = 0; i < *regalsSize; i++){
        free((*regals)[i].m_Product);
    }
    free(*regals);
}

void freeRegalsSorted(TREG ** regalsSorted, int * regalsSortedSize)
{
    for (int i = 0; i < *regalsSortedSize; i++){
        free((*regalsSorted)[i].m_Product);
    }
    free(*regalsSorted);
}

void freeShoppingList(TLIST ** shoppingList, int * shoppingListSize){
    for (int i = 0; i < *shoppingListSize; i++){
        free((*shoppingList)[i].m_Product);
    }
    free(*shoppingList);
}


int main ( void )
{   
    int regalsMaxSize = 10, shoppingListMaxSize = 10;
    int regalsSize = 0, shoppingListSize = 0;
    int numOfRegals, res;
    TREG * regals = (TREG*) malloc (regalsMaxSize * sizeof(*regals));
    TLIST * shoppingList = NULL;

    /* Reads the products from the regals and saves them into the struct shoppingList */
    if (!readRegals(&regals, &regalsSize, &regalsMaxSize, &numOfRegals)){
        freeRegals(&regals, &regalsSize);
        printf("Nespravny vstup.\n");
        return 1;
    }
    TREG * regalsSorted = (TREG*) malloc (regalsSize * sizeof(*regalsSorted));
    for (int i = 0; i < regalsSize; i++){
        regalsSorted[i].m_Product = (char*)malloc((strlen(regals[i].m_Product)+1)*sizeof(char));
        strcpy(regalsSorted[i].m_Product, regals[i].m_Product);
        regalsSorted[i].m_RegalID = regals[i].m_RegalID;
    }
    qsort(regalsSorted, regalsSize, sizeof(*regalsSorted), (int(*)(const void *, const void *))cmpStr);
    while ( 1 ) {
       
        res = readShoppingList(&shoppingList, &shoppingListSize, &shoppingListMaxSize, numOfRegals);
        optimalizeList( &shoppingList, &regals, &regalsSorted, &regalsSize, &shoppingListSize, numOfRegals);
        printOptimalizedList(&shoppingList, &shoppingListSize, numOfRegals);
        
        if (shoppingListSize != 0){
            freeShoppingList(&shoppingList, &shoppingListSize);
            shoppingList = NULL;
            shoppingListSize = 0;
            shoppingListMaxSize = 0;
        }
        if (res == -1) break;
    }
    if (!feof(stdin)){
        printf("Nespravny vstup.\n");
        freeRegals(&regals, &regalsSize);
        freeRegalsSorted(&regalsSorted, &regalsSize);
        freeShoppingList(&shoppingList, &shoppingListSize);
        return 1;
    }
    freeRegals(&regals, &regalsSize);
    freeRegalsSorted(&regalsSorted, &regalsSize);
    return 0;
}
