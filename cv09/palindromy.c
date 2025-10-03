#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void removeSpaces(char * str)
{
    char * d = str;
    while (*str){
        if (!isblank(*str))
            *d++ = *str++;
        else 
            str++;
    }
    *d = '\0';
}

int validateLine(char * line)
{
    int l = strlen(line);
    if (line[0] == '\n')
        return 0;
    if (l > 0 && line[l-1] != '\n')
        return 0;
    for (int i = 0; i < l-1; i++)
    {
        if (!isspace (line[i]))
            return 1;
    }
    return 0;
}

void stripLF (char * line)
{
    int length = strlen(line);
    if (length > 0 && line[length-1] == '\n')
        line[length-1] = '\0';
}

int isPalyndrome(char * str)
{
    char * back = str + strlen(str) - 1;
    while (str < back){
        if (tolower(*str) != tolower(*back))
            return 0;
        ++str;
        --back;
    }
    return 1;
}

int isPalyndromeSensitive(char * str)
{
    char * back = str + strlen(str) - 1;
    while (str < back){
        if (*str != *back)
            return 0;
        ++str;
        --back;
    }
    return 1;
}

int main ( void )
{
    char * str = NULL;
    size_t capacity = 0;
    printf("Zadejte retezec:\n");
    while (getline(&str, &capacity, stdin) != -1){
        if (!validateLine(str)){
            printf("Nespravny vstup.\n");
            free(str);
            return 1;
        }
        stripLF(str);
        removeSpaces(str);
        if ( isPalyndrome(str) ){
            if ( isPalyndromeSensitive(str))
                printf("Retezec je palindrom (case-sensitive).\n");
            else 
                printf("Retezec je palindrom (case-insensitive).\n");
        } else {
            printf("Retezec neni palindrom.\n");
        }
    }
    free(str);
    return 0;
}
