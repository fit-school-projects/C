#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LOG
{
    char *id;
    int salary;
} LOG;

typedef struct SALARY_COUNT
{
    int salary;
    size_t count;
} SALARY_COUNT;

typedef struct LOG_ARR
{
    LOG *data;
    size_t n, size;
} LOG_ARR;

typedef struct COUNT_ARR
{
    SALARY_COUNT *data;
    size_t n, size;
} COUNT_ARR;

void addLog(char *id, int salary, LOG_ARR *arr)
{
    //printf("Adding log\n");

    if (arr->n >= arr->size)
    {
        arr->size = (arr->size * 2) + 1;
        arr->data = (LOG *)realloc(arr->data, sizeof(LOG) * arr->size);
    }
    LOG element;
    element.salary = salary;
    element.id = strdup(id);
    arr->data[arr->n++] = element;
}

void addCount(int salary, COUNT_ARR *arr)
{
    if (arr->n >= arr->size)
    {
        arr->size = (arr->size * 2) + 1;
        arr->data = (SALARY_COUNT *)realloc(arr->data, sizeof(SALARY_COUNT) * arr->size);
    }
    SALARY_COUNT element;
    element.count = 1;
    element.salary = salary;
    arr->data[arr->n++] = element;
}

void freeCountArr(COUNT_ARR *arr)
{  
    free(arr->data);
}

int isValid(char *str)
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9')
        {
            continue;
        }
        return 0;
    }
    return 1;
}

void freeLogArr(LOG_ARR *arr)
{
    for (size_t i = 0; i < arr->n; i++)
    {
        free(arr->data[i].id);
    }
    free(arr->data);
}

int main()
{
    LOG_ARR logs;
    logs.n = 0;
    logs.size = 10;
    logs.data = (LOG *)malloc(sizeof(LOG) * logs.size);


    int readingQuestions = 0;
    int readLog = 0;
    int scanCode;
    char c;
    while ((scanCode = scanf("%c", &c)) == 1)
    {
        //printf("%c, reading questions: %d\n", c, readingQuestions);

        if (!readingQuestions && c == '+')
        {
            //printf("Inside + if\n");

            readLog = 1;

            char str1[11];
            int num1;
            if (scanf(" %10s %d ", str1, &num1) != 2)
            {
                freeLogArr(&logs);
                printf("fail in reading logs\n");
                return EXIT_FAILURE;
            }
            else
            {
                if (isValid(str1))
                {
                    addLog(str1, num1, &logs);
                }
            }
        }
        else if(c == '?' && readLog)
        {
            readingQuestions = 1;

            COUNT_ARR counts;
            counts.n = 0;
            counts.size = 10;
            counts.data = (SALARY_COUNT *)malloc(sizeof(SALARY_COUNT) * counts.size);
            
            size_t maxCount = 0;
            char str2[11];
            if (scanf(" %10s ", str2) != 1)
            {
                freeLogArr(&logs);
                printf("fail in reading questions\n");
                return EXIT_FAILURE;
            }
            else
            {
                for (size_t i = 0; i < logs.n; i++)
                {
                    if (strncmp(logs.data[i].id, str2, strlen(str2)) == 0 || strncmp(str2, "*", 1) == 0)
                    {
                        int found = 0;

                        for (size_t j = 0; j < counts.n; j++)
                        {
                            if (logs.data[i].salary == counts.data[j].salary)
                            {
                                counts.data[j].count++;
                                found = 1;
                                if (maxCount < counts.data[j].count)
                                {
                                    maxCount = counts.data[j].count;
                                }
                            }
                        }
                        
                        if (found == 0)
                        {
                            addCount(logs.data[i].salary, &counts);
                            if (maxCount == 0)
                            {
                                maxCount = 1;
                            }
                            
                        }
                    }
                    
                }
                
            }

            if (maxCount == 0)
            {
                printf("Modus: N/A\n");
            }
            else
            {
                int printingFirst = 1;
                for (size_t i = 0; i < counts.n; i++)
                {
                    if (counts.data[i].count == maxCount)
                    {
                        if (printingFirst)
                        {
                            printf("Modus: %d", counts.data[i].salary);
                            printingFirst = 0;
                        }
                        else
                        {
                            printf(", %d", counts.data[i].salary);
                        }
                    }
                }
                printf(" [%zu]\n", maxCount);
            }

            freeCountArr(&counts);
        }
        else
        {
            freeLogArr(&logs);
            printf("fail read a char but not plus or question mark\n");
            return EXIT_FAILURE;
        }
    }

    if (scanCode != EOF)
    {
        freeLogArr(&logs);
        printf("fail after while\n");
        return EXIT_FAILURE;
    }
    
    freeLogArr(&logs);
    return EXIT_SUCCESS;
}
