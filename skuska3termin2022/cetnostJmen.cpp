#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Names
{
    char * m_Name;
    int    m_NumberOfOccasions;
} TNAME;

int cmpInt(const void * a, const void * b)
{
    TNAME * aPtr = (TNAME*)a;
    TNAME * bPtr = (TNAME*)b;
    if (aPtr->m_NumberOfOccasions < bPtr->m_NumberOfOccasions)
        return 1;
    else if (aPtr->m_NumberOfOccasions > bPtr->m_NumberOfOccasions)
        return -1;
    return 0;
}

void readInput( TNAME ** names, int * sizeNames, int * maxSizeNames)
{
    int lengthOfBuffer = 0, lengthOfName = 0;
    char * buffer = NULL;
    size_t capacity = 0;
    char * partOfName = (char*) malloc (100 * sizeof(*partOfName));

    while ( getline (&buffer, &capacity, stdin) != -1 ){
        for (int i = 0; i < lengthOfName; i++){
            partOfName[i] = '\0';
        }

        lengthOfName = 0;
        lengthOfBuffer = 0;

        while (buffer[lengthOfBuffer] != '\n'){
            if (!isspace(buffer[lengthOfBuffer])){
                partOfName[lengthOfName++] = buffer[lengthOfBuffer++];
                continue;
            }
            if (isspace(buffer[lengthOfBuffer]) && partOfName[0] != '\0'){
                partOfName[lengthOfName + 1] = '\0';
                for (int i = 0; i < *sizeNames; i++){
                    if (strcmp((*names)[i].m_Name, partOfName) == 0){
                        (*names)[i].m_NumberOfOccasions += 1;
                        continue;
                    }
                }
                // reallocating the memory needed for the next name
                if (*sizeNames >= *maxSizeNames){
                    *maxSizeNames += *maxSizeNames / 2 + 10;
                    *names = (TNAME*) realloc (*names, *maxSizeNames * sizeof(**names));
                }
                
                (*names)[*sizeNames].m_Name = partOfName;
                (*names)[*sizeNames].m_NumberOfOccasions = 1;
                (*sizeNames)++;
                
                partOfName = (char*) malloc (100 * sizeof(*partOfName));
                
                lengthOfName = 0;
                lengthOfBuffer++;
            } else {
                lengthOfBuffer++;
            }
        }
    }

    free(buffer);
}

int main ( void )
{
    int sizeName = 0, maxSizeName = 10, max = 0;
    TNAME * name = (TNAME*) malloc (maxSizeName * sizeof(TNAME));
    readInput(&name, &sizeName, &maxSizeName);
    
    qsort(name, sizeName, sizeof(*name), (int(*)(const void *, const void *))cmpInt );
    max = name[0].m_NumberOfOccasions;
    
    printf("Nejcastejsi jmeno: %dx\n", max);
    
    for (int i = 0; i < sizeName; i++){
        if (name[i].m_NumberOfOccasions == max){
            printf("%s\n", name[i].m_Name);
        }
    }
    
    for (int i = 0; i < sizeName; i++){
        free(name[i].m_Name);
    }
    free(name);
    return 0;
}
