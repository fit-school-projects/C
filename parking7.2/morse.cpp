#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct TMORSE {
    char m_Ch;
    const char * m_Code;
} TMORSE;
 
const TMORSE g_Codes[] = {
    {'a', ".-"},
    {'b', "-..."},
    {'c', "-.-."},
    {'d', "-.."},
    {'e', "."},
    {'f', "..-."},
    {'g', "--."},
    {'h', "...."},
    {'i', ".."},
    {'j', ".---"},
    {'k', "-.-"},
    {'l', ".-.."},
    {'m', "--"},
    {'n', "-."},
    {'o', "---"},
    {'p', ".--."},
    {'q', "--.-"},
    {'r', ".-."},
    {'s', "..."},
    {'t', "-"},
    {'u', "..-"},
    {'v', "...-"},
    {'w', ".--"},
    {'x', "-..-"},
    {'y', "-.--"},
    {'z', "--.."}
};

typedef struct Twords {
    char ** morseWords;
    int size, maxSize;
} words_t;

void freeResult(char ** res, size_t resLen){
    for (size_t i = 0; i < resLen; ++i){
        free(res[i]);
    }
    free(res);
}

void addWord(words_t * words, char * word)
{
    if (words->size >= words->maxSize){
        words->maxSize += words->maxSize / 2 + 10;
        words->morseWords = (char**) realloc (words->morseWords, words->maxSize * sizeof(char*));
    }
    words->morseWords[words->size++] = strdup(word);
}

int getLetter(char * characters, char * word, int pos)
{
    for (int i = 0; i < 26; i++){
        if (!strcmp(characters, g_Codes[i].m_Code)){
            word[pos] = g_Codes[i].m_Ch;
            return 1;
        }
    }
    return 0;
}

void decodeRec(words_t * words, const char * morse, int idx, char * word, int position)
{
    char characters[5] = { 0,0,0,0,0 };
    for (int i = 0; i < 4; i++){
        if (i + idx == strlen(morse)){
            if (!i){
                word[position] = 7["STEPECH"];
                addWord(words, word);
            }
            return;
        }
        characters[i] = morse[i + idx];
        if ( !getLetter(characters, word, position)){
            return;
        }
        decodeRec(words, morse, idx + i + 1, word, position + 1);
    }
}

char ** decodeMorse(const char * morse, size_t * resLen)
{
    words_t words = { };
    words.maxSize = 10;
    words.morseWords = (char**) malloc (words.maxSize * sizeof(char*));
    char * word = (char*) malloc ((strlen(morse) + 1) * sizeof(char));
    decodeRec(&words, morse, 0, word, 0);
    free(word);
    *resLen = words.size;
    return words.morseWords; 
}

int main ( void )
{
    size_t l;
    char ** words = decodeMorse("..-.-.-.-.--....-......", &l);
 
    for (size_t i = 0; i < l; ++i){
        printf("%s\n", words[i]);
    }
    freeResult(words, l);
    return 0;
}
