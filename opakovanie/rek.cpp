#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Tcode {
    char m_Code[12];
    int  m_Len;
    char * m_Spaces;
    int m_Count;
} TCODE;

int validateCode(char * code)
{
    for (int i = 0; i < strlen(code); i++){
        if(!isdigit(code[i])){
            return 0;
        }
    }
    return 1;
}
int readInput(TCODE * code)
{
    if ( scanf("%11s", code->m_Code) != 1 || strlen(code->m_Code) > 10 || !validateCode(code->m_Code))
        return 0;
    return 1;
}

int isDivisibleByThree(char * buffer, TCODE * code)
{
    int sum = 0;
    for (int i = 0; i < code->m_Len; i++){
        sum += buffer[i];
    }
    if (sum % 3 == 0){
        return 1;
    }
    return 0;
}

int validateOption(TCODE * code)
{
    char * buffer = (char*)calloc(code->m_Len*2, sizeof(char));
    for (int i = 0; i < code->m_Len; i++){
        if (code->m_Spaces[i]){
            if (!isDivisibleByThree(buffer, code)){
                free(buffer);
                buffer = NULL;
                return 0;
            } else {
                free(buffer);
                buffer = NULL;
                buffer = (char*)calloc(code->m_Len*2, sizeof(char));
            }
        }
        strncat(buffer, &code->m_Code[i], 1);
    }
    if (!isDivisibleByThree(buffer, code)){
        free(buffer);
        buffer = NULL;
        return 0;
    } else {
        free(buffer);
        buffer = NULL;
    }
    return 1;
}

void getCodeRek(TCODE * code, int idx, int isSpace)
{
    code->m_Spaces[idx] = isSpace;

    if (idx == code->m_Len - 1 ){
        if (!validateOption(code))
            return;
        for (int i = 0; i < code->m_Len; i++){
            if (code->m_Spaces[i]){
                printf(" ");
            }
            printf("%c", code->m_Code[i]);
        }
        printf("\n");
        code->m_Count += 1;
        return;
    }

    getCodeRek(code, idx + 1, 0);
    getCodeRek(code, idx + 1, 1);
}

int main ( void )
{
    TCODE code = { };
    printf("Zadaj kod:\n");
    if ( !readInput(&code)){
        printf("Nespravny vstup.\n");
        return 1;
    }

    code.m_Len = strlen(code.m_Code);
    code.m_Spaces = (char*) calloc (10000, sizeof(char));

    getCodeRek(&code, 0, 0);
    printf("Celkom: %d\n", code.m_Count);

    return 0;
}
