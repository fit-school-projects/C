#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct TNames{
    char * m_Name;
} TNAME;

typedef struct TPerson
{
    TNAME * m_Names;
    int     m_Count;
    int     m_MaxCount;
} TPERSON;

void appendChar(char ** name, int * sizeName, char character)
{
    (*name)[*sizeName++] = character;
}

void readInput(TPERSON ** person, int * sizePerson, int * maxSizePerson)
{
    char * line = NULL;
    size_t capacity = 0;

    while (getline(&line, &capacity, stdin) != -1)
    {
        if (*sizePerson >= *maxSizePerson){
            *maxSizePerson += *maxSizePerson / 2 + 10;
            *person = (TPERSON*) realloc (*person, *maxSizePerson * sizeof(**person));
        }
        (*person)[*sizePerson].m_Count = 0;
        (*person)[*sizePerson].m_MaxCount = 10;
        (*person)[*sizePerson].m_Names = (TNAME*) malloc ((*person)[*sizePerson].m_MaxCount * sizeof(TNAME));

        char * name = (char*) malloc ((strlen(line) + 1) * sizeof(char));
        int sizeName = 0;
        int wasAlpha = 0;
        while ( *line != '\n')
        {
            if (isalpha(*line))
            {
                appendChar(&name, &sizeName, *line);
            }  
            if (!isalpha(*line) && wasAlpha == 1){
                appendChar(&name, &sizeName, '\0');
                (*person)[*sizePerson].m_Names[(*person)[*sizePerson].m_Count++].m_Name = name;
                char * name = (char*) malloc ((strlen(line) + 1) * sizeof(char));
                int sizeName = 0;
                line++;
            } else {
                line++;
            }
        } 
        (*sizePerson)++;
    }
    free(line);
}

void printOutput(TPERSON * person, int size)
{
    for (int i = 0; i < size; i++){
        for ( int j = 0; j < person[i].m_Count; j++){
            printf("%s ", person[i].m_Names[j].m_Name);
        }
        printf("\n");
    }
}

int main ( void )
{
    int sizePerson = 0, maxSizePerson = 10;
    TPERSON * person = (TPERSON*) malloc (maxSizePerson * sizeof(*person));

    readInput(&person, &sizePerson, &maxSizePerson);
    printOutput(person, sizePerson);

    return 0;
}
