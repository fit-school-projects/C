#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN_CODE 102

typedef struct Tcode
{
    char m_Code[MAX_LEN_CODE];
    char * m_Spaces;
    int m_Len;
    int max;
    int min;
    int m_Count;
} TCODE;

int validateCode(const char * code)
{
    for (int i = 0; i < strlen(code); i++){
        if (!isalpha(code[i]))
            return 0;
    }
    return 1;
}

int readInput(TCODE * code)
{
    printf("word\n");
    if(scanf(" %101s", code->m_Code) != 1 || strlen(code->m_Code) > 100 || !validateCode(code->m_Code))
        return 0;
    printf("min max\n");
    if (scanf(" %d %d", &code->min, &code->max) != 2 || code->min > code->max || code->min <= 0 || code->max <= 0)
        return 0;
    code->m_Len = strlen(code->m_Code);
    return 1;
}

int isNumInInterval(char * buffer, TCODE * code)
{   
    if (strlen(buffer) >= code->min && strlen(buffer) <= code->max)
        return 1;
    return 0; 
}

void getSpacesRec(TCODE * code, int idx, int isSpace)
{
    code->m_Spaces[idx] = isSpace;

    if (idx == code->m_Len - 1){
        // char * buffer = (char*) calloc (code->m_Len*2, sizeof(char));
        int count = 0;
        for (int i = 0; i < code->m_Len; i++){
            if (code->m_Spaces[i]){
                count++;
                /**
                if (!isNumInInterval(buffer, code)){
                free(buffer);
                buffer = NULL;
                return;
                } else {
                    free(buffer);
                    buffer = NULL;
                    buffer = (char*) calloc (code->m_Len*2, sizeof(char));
                }
                */
            }
            //strncat(buffer, &code->m_Code[i], 1);
        }
        if (!((count + 1) >= code->min && (count + 1) <= code->max))
            return;
        /**
        if (!isNumInInterval(buffer, code)){
            free(buffer);
            buffer = NULL;
            return;
        } else {
            free(buffer);
            buffer = NULL;
            buffer = (char*) calloc (code->m_Len*2, sizeof(char));
        }
        */

        for (int i = 0; i < code->m_Len; i++){
            if (code->m_Spaces[i]){
                printf(" ");
            }
            printf("%c", code->m_Code[i]);
        }
        printf("\n");
        code->m_Count++;
        return;
    }   

    getSpacesRec(code, idx + 1, 0);
    getSpacesRec(code, idx + 1, 1);
}

int main ( void )
{
    TCODE code = { };
    if(!readInput(&code)){
        puts("Nespravny vstup");
        return 1;
    }
    code.m_Spaces = (char*) calloc (10000, sizeof(char));
    getSpacesRec(&code, 0, 0);
    printf("Celkom: %d\n", code.m_Count);
    return 0;
}
