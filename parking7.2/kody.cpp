#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct Tstring {
    char m_String[26];
    int  m_Len;
    int  m_Count;
} string_t;

int validateString(char * string)
{
    for (int i = 0; i < strlen(string); i++){
        if(!isalpha(string[i]) && string[i] != '?')
            return 0;
    }
    return 1;
}

int readString(string_t * string)
{
    if (scanf(" %12s", string->m_String) != 1 || strlen(string->m_String) > 10 || !validateString(string->m_String))
    {
        return 0;
    }
    string->m_Len = strlen(string->m_String);
    return 1;
}

void readFormat(char * newString, int idx, string_t * characters, string_t * format)
{
    if (format->m_String[idx] != '?'){
        characters->m_String[0] = format->m_String[idx];
        characters->m_Len = 1;
    } else if ( !idx ){
        for (int i = 0; i < 26; i++){
            characters->m_String[i] = i + 'a';
        }
        characters->m_Len = 26;
    } else {
        for (int i = newString[idx-1] - 2; i <= newString[idx-1] + 2; i++){
            if (i >= 'a' && i <= 'z'){
                characters->m_String[characters->m_Len++] = i;
            }
        }
    }
}

void getRec(string_t * format, char * newString, int idx)
{
    string_t characters = { };
    readFormat(newString, idx, &characters, format);

    for (int i = 0; i < characters.m_Len; i++){
        /**
        if (idx > 0 && fabs(newString[idx - 1] - characters.m_String[i]) > 2){
            continue;
        }
        */
        newString[idx] = characters.m_String[i];
        if (idx == format->m_Len - 1){
            puts(newString);
            format->m_Count++;
        } else {
            getRec(format, newString, idx + 1);
        }
    }
}

int main ( void )
{
    string_t string = { };
    if ( !readString(&string)){
        printf("Nespravny vstup.\12");
        return 1;
    }
    char * newString = (char*) calloc (string.m_Len, sizeof(char));
    getRec(&string, newString, 0);
    printf("Celkom: %d\12", string.m_Count);
    free(newString);
    return 0; 
}
