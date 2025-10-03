#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

typedef struct Titem {
    char * m_Word;
    struct Titem * m_Next;
    struct Titem * m_NextWord;
    struct Titem * m_PrevWord;
} TITEM;

TITEM * nodeCreate(char * word, int sizeWord, TITEM * next)
{
    TITEM * node = (TITEM*) malloc (sizeof(*node));
    node->m_Word = (char*) malloc (sizeWord * sizeof(char));
    strncpy(node->m_Word, word, sizeWord);
    node->m_Next = next;
    node->m_NextWord = NULL;
    node->m_PrevWord = NULL;
    return node;
}

void listDelete(TITEM * list)
{
    while (list){
        TITEM * tmp = list->m_Next;
        free(list->m_Word);
        free(list);
        list = tmp;
    }
}

void printList(TITEM * list)
{
    TITEM * tmp = list;
    printf("HEAD");
    while (tmp){
        printf(" -> %s", tmp->m_Word);
        tmp = tmp->m_Next;
    }
    printf("\n");
}

void appendChar(char ** word, int * sizeWord, int * maxSizeWord, char character)
{
    if (*sizeWord >= *maxSizeWord){
        *maxSizeWord += *maxSizeWord / 2 + 10;
        *word = (char*) realloc (*word, *maxSizeWord * sizeof(**word));
    }
    (*word)[*sizeWord] = character;
    (*sizeWord)++;
}

TITEM * pushBack(TITEM ** list, char * word, int sizeWord)
{
    if (*list == NULL){
        *list = nodeCreate(word, sizeWord, *list);
        return *list;
    }
    TITEM * current = *list;
    while (current->m_Next != NULL)
        current = current->m_Next;
    current->m_Next = nodeCreate(word, sizeWord, NULL);
    return current->m_Next;
}

void findNextAndPrev(TITEM * res, char * word, TITEM * current)
{
    if (res->m_Next == NULL) 
        return;
    TITEM * tmp = res;
    while (tmp){
        if (strcmp(tmp->m_Word, current->m_Word) == 0){
            if (tmp->m_NextWord == NULL)
                tmp->m_NextWord = current;
            current->m_PrevWord = tmp;
            return;
        }
        tmp = tmp->m_Next;
    }
}

TITEM * stringToList( const char * string )
{
    TITEM * res = NULL;
    TITEM * current;
    int sizeWord = 0, maxSizeWord = 10; 
    int wasAlpha = 0;
    char * word = (char*) malloc (maxSizeWord * sizeof(*word));
    int pos = 0;
    int wordLength = strlen(string) + 1;
    while (wordLength){
        if (!isalpha(string[pos]) && wasAlpha){
            appendChar(&word, &sizeWord, &maxSizeWord, '\0');
            current = pushBack(&res, word, sizeWord);
            findNextAndPrev(res, word, current);
            sizeWord = 0;
            maxSizeWord = 0;
            free(word);
            word = NULL;
            wasAlpha = 0;
        }
        else if (isalpha(string[pos])){
            appendChar(&word, &sizeWord, &maxSizeWord, string[pos]);
            wasAlpha = 1;
        }
        pos++;
        wordLength--;
    }
    
    return res;
}

int main ( void )
{
    TITEM * res;
    res = stringToList("ja ja");
    assert(res->m_NextWord == res->m_Next);
    assert(res->m_Next->m_PrevWord == res);
    assert(res->m_PrevWord == NULL);
    assert(res->m_Next->m_NextWord == NULL);
    printList(res);
    listDelete(res);

    return 0;
}
