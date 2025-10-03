#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Tcode {
    char m_Code[102];
    int  m_Len;
    int * m_Spaces;
    int  m_Count;
} TCODE;

int readCode(TCODE * code)
{
    printf("Data:\n");
    if ( scanf("%11s", code->m_Code) != 1 || strlen(code->m_Code) > 10){
        return 0;
    }
    return 1;
}

int validateNum(char * buffer)
{
    char character;
    int sum = 0;
    while ( sscanf(buffer, "%c", &character) == 1){
        buffer++;
        sum += character - '0';
    }
    if (sum % 3 == 0){
        return 1;
    }
    return 0;
}

void genRek(TCODE * c, int idx, int isSpace)
{
    c->m_Spaces[idx] = isSpace;
    if (c->m_Len - 1 == idx){
        char * buffer = (char*)malloc(c->m_Len*2*sizeof(char));
        for (int i = 0; i < c->m_Len; i++){
            if (c->m_Spaces[i] == 1){
                if (!validateNum(buffer)){
                    free(buffer);
                    buffer = NULL;
                    return;
                }
                free(buffer);
                buffer = NULL;
                buffer = (char*)malloc(c->m_Len*2*sizeof(char));
            }
            strncat(buffer, &c->m_Code[i], 1);
        }
        if (!validateNum(buffer)){
            free(buffer);
            buffer = NULL;
            return;
        } else {
            free(buffer);
            buffer = NULL;
        }

        // print 
        for (int i = 0; i < c->m_Len; i++){
            if (c->m_Spaces[i] == 1){
                printf(" ");
            }
            printf("%c", c->m_Code[i]);
        }
        printf("\n");
        c->m_Count ++;
        return;
    }
    genRek(c, idx + 1, 0);
    genRek(c, idx + 1, 1);
}

int main ( void )
{
    TCODE code = { };

    if ( !readCode(&code)){
        printf("Nepsravny vstup.\n");
        return 1;
    }
    code.m_Len = strlen(code.m_Code);
    code.m_Spaces = (int*) calloc (100000, sizeof(int));
    genRek(&code, 0, 0);
    printf("Celkom %d\n", code.m_Count);
    free(code.m_Spaces);
    return 0;
}
