#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLENGTH 31

typedef struct TVocabulary {
    char * m_VocabWord;
} TVOCAB;

typedef struct TSentence {
    char * m_SentenceWord;
    int isInVocabulary;
    int wordLength;
} TSENTENCE;

int vocabCmp(const void * a, const void * b)
{
    TVOCAB * aPtr = (TVOCAB*)a;
    TVOCAB * bPtr = (TVOCAB*)b;

    return strcasecmp(aPtr->m_VocabWord, bPtr->m_VocabWord);
}

int cmpSentenceWord(const void * a, const void * b)
{
    char * aPtr = (char*)a;
    TVOCAB * bPtr = (TVOCAB*)b;

    return strcasecmp(aPtr, bPtr->m_VocabWord);
}

void appendChar (char ** word, int * sizeWord, int * maxSizeword, char character)
{
    if (*sizeWord >= *maxSizeword){
        *maxSizeword += *maxSizeword / 2 + 10;
        *word = (char*) realloc (*word, *maxSizeword * sizeof(char));
    }
    (*word)[*sizeWord] = character;
    (*sizeWord)++;
}

int readVocabulary(TVOCAB ** vocabulary, int * sizeVocabulary, int * maxSizeVocabulary)
{
    char * line = NULL;
    size_t capacity = 0;
    if ( getline(&line, &capacity, stdin) == -1){
        free(line);
        return EOF;
    }  
    int sizeWord = 0, maxSizeWord = 10;
    char * word = (char*) malloc (maxSizeWord * sizeof(*word));
    int lineLength = strlen(line);
    while (lineLength){
        if (isspace(line)){
            line++;
            lineLength--;
            char * word = (char*) malloc (maxSizeWord * sizeof(*word));
        } else {
            appendChar();
        }
    }
    if ( strcmp("*****", line) == 0 ){
        free(line);
        return 2;
    }
    if (*sizeVocabulary >= *maxSizeVocabulary){
        *maxSizeVocabulary += *maxSizeVocabulary / 2 + 10;
        *vocabulary = (TVOCAB*) realloc (*vocabulary, *maxSizeVocabulary * sizeof(**vocabulary));
    }
    int wordLength = strlen(word) + 1;
    (*vocabulary)[*sizeVocabulary].m_VocabWord = (char*) malloc (wordLength * sizeof(char));
    (*vocabulary)[*sizeVocabulary].m_VocabWord = word;
    (*sizeVocabulary)++;

    free(line);
    return 1;
}

int readSentence(TVOCAB * vocabulary, TSENTENCE ** sentence, int * maxSizeSentence, int * sizeSentence, int sizeVocabulary)
{
    int res;
    char * word = NULL;
    size_t capacity = 0;
    char sentenceWord[MAXLENGTH];
    while ( getdelim(&word, &capacity, ' ', ) != -1){
        if (*sizeSentence >= *maxSizeSentence){
            *maxSizeSentence += *maxSizeSentence / 2 + 10;
            *sentence = (TSENTENCE*) realloc (*sentence, *maxSizeSentence * sizeof(**sentence));
        }
        strcpy((*sentence)[*sizeSentence].m_SentenceWord, sentenceWord);
        if (bsearch(sentenceWord, vocabulary, sizeVocabulary, sizeof(TVOCAB), cmpSentenceWord)){
            (*sentence)[*sizeSentence].isInVocabulary = 1;
            (*sentence)[*sizeSentence].wordLength = strlen(sentenceWord);
        } else {
            (*sentence)[*sizeSentence].isInVocabulary = 0;
            (*sentence)[*sizeSentence].wordLength = strlen(sentenceWord) + 11;
        }
        (*sizeSentence)++;
    }
    return 1;
}


int main ( void )
{
    int sizeVocabulary = 0, maxSizeVocabulary = 10, res;
    int sizeSentence = 0, maxSizeSentence = 10;

    TVOCAB * vocabulary = (TVOCAB*) malloc (maxSizeVocabulary * sizeof(*vocabulary));
    TSENTENCE * sentence = (TSENTENCE*) malloc (maxSizeSentence * sizeof(*sentence));

    printf("Slovnik:\n");
    while ( ( res = readVocabulary(&vocabulary, &sizeVocabulary, &maxSizeVocabulary)) == 1){}
    if (res == EOF || res == 0){
        printf("Nespravny vstup.\n");
        free(sentence);
        free(vocabulary);
        return 1;
    }
    qsort(vocabulary, sizeVocabulary, sizeof(TVOCAB), vocabCmp);

    for (int i = 0; i < sizeVocabulary; i++){
        printf("%s\n", vocabulary[i].m_VocabWord);
    }
    
    if (res == 2){
        printf("Text:\n");
        readSentence(vocabulary, &sentence, &maxSizeSentence, &sizeSentence, sizeVocabulary);
    }
    int lineLength = 0;
    for (int i = 0; i < sizeSentence; i++ ){
        if (sentence[i].isInVocabulary == 1){
            printf("%s", sentence[i].m_SentenceWord);
        } else {
            printf("<err>%s</err>", sentence[i].m_SentenceWord);
        }
        lineLength += sentence[i].wordLength;
        if ( i + 1 != sizeSentence){
            if (lineLength + sentence[i + 1].wordLength > 80){
                printf("\n");
                lineLength = 0;
            } else {
                printf(" ");
                lineLength++;
            }
        }
    }
    printf("\n");
    free(sentence);
    free(vocabulary);
    return 0;
}
