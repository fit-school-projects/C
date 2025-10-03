#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
 
typedef struct salaryRecord{
    char regions[11];
    int salary;
} SALARY_RECORD;
 
typedef struct salaryArray{
    SALARY_RECORD * salaries;
    size_t len,cap;
} SALARY_ARR;
 
typedef struct salaryCounter{
    int salary;
    size_t number_of_occurences;
} SALARY_COUNTER;
 
typedef struct salariesCount{
    SALARY_COUNTER * data;
    size_t len,cap;
} SALARIES_COUNT;
 
void initializeSalaryArr(SALARY_ARR * arr){
    arr->salaries = NULL;
    arr->len = arr->cap = 0;
}
 
void destroySalaryArr(SALARY_ARR * arr){
    free(arr->salaries);
    initializeSalaryArr(arr);
}
 
void appendSalaryToArr(SALARY_ARR * arr, SALARY_RECORD * record){
    if(arr->len >= arr->cap){
        arr->cap = 2 * arr->cap + 16;
        arr->salaries = (SALARY_RECORD*)realloc(arr->salaries, sizeof(arr->salaries[0]) * arr->cap);
    }
 
    arr->salaries[arr->len++] = *record;
}
 
void initializeSalaryCounts(SALARIES_COUNT * arr){
    arr->data = NULL;
    arr->len = arr->cap = 0;
}
 
void destroySalariesCount(SALARIES_COUNT * arr){
    free(arr->data);
    initializeSalaryCounts(arr);
}
 
void appendToSalariesCount(SALARIES_COUNT * arr, SALARY_COUNTER * counter){
    if(arr->len >= arr->cap){
        arr->cap = 2 * arr->cap + 16;
        arr->data = (SALARY_COUNTER*)realloc(arr->data, sizeof(arr->data[0]) * arr->cap);
    }
 
    arr->data[arr->len++] = *counter;
}
 
bool checkIfInSalariesCount(SALARIES_COUNT * arr, int salary, int * index){
    for(size_t i = 0; i < arr->len; i++){
        // printf("kontrolujem %d s %d\n", arr->data[i].salary , salary);
        if(arr->data[i].salary == salary){
            *index = i;
            return true;
        }
    }
    return false;
}
 
void findModusOfSalary(SALARIES_COUNT * arr, size_t * indexes, size_t * indexes_count){
    size_t max = 0;
    //naivne predpokladame ze viac ako 1000 nebude mat rovnaku cetnost (3 dynamicke polia sa mi robit fakt neche :DD)
    size_t j = 0;
 
    for(size_t i = 0; i < arr->len; i++){
        if(arr->data[i].number_of_occurences > max){
            max = arr->data[i].number_of_occurences;
            j = 0;
            indexes[j] = i;
        }else if(arr->data[i].number_of_occurences == max){
            indexes[++j] = i;
        }
    }
 
   *indexes_count = j;
}
 
bool checkIfIsInRegion(char a[11], char b[11], size_t len){
    for(size_t i = 0; i < len; i++){
        if(a[i] != b[i])
            return false;
    }
    return true;
}
 
bool loadSalaries(SALARY_ARR * arr){
    SALARY_RECORD new_record;
    int res = scanf("%10s %d", new_record.regions, &new_record.salary);
 
    //TODO kontrola vstupu!!!
    if(res != 2)
        return false;
 
    appendSalaryToArr(arr, &new_record);
    return true;
}
 
bool getSalaryStatistics(SALARY_ARR * arr){
    char buffer[11];
    int res = scanf("%10s", buffer);
 
    if(res != 1)
        return false;
 
    SALARIES_COUNT salaries_count;
    initializeSalaryCounts(&salaries_count);
    int index;
 
    if(!strcmp(buffer, "*")){
        for(size_t i = 0; i < arr->len; i++){
            if(checkIfInSalariesCount(&salaries_count, arr->salaries[i].salary, &index)){
                salaries_count.data[index].number_of_occurences++;
            }else{
                SALARY_COUNTER new_counter = {arr->salaries[i].salary, 1};
                appendToSalariesCount(&salaries_count, &new_counter);
            }
            // puts("SALARIES COUNT ARRAY");
            // size_t p = 0;
            // while(p < salaries_count.len){
            //     printf("%d %ld\n", salaries_count.data[p].salary, salaries_count.data[p].number_of_occurences);
            //     p++;
            // }
        }
    }else{
        size_t i = 0;
        size_t buffer_len = 0;
        while(buffer[i] != '\0'){
            if(!isdigit(buffer[i]))
                return false;
            i++;
            buffer_len++;
        }
 
        bool region_found = false;
 
        for(size_t i = 0; i < arr->len; i++){
            if(checkIfIsInRegion(arr->salaries[i].regions, buffer, buffer_len)){
                region_found = true;
                if(checkIfInSalariesCount(&salaries_count, arr->salaries[i].salary, &index)){
                    salaries_count.data[index].number_of_occurences++;
                }else{
                    SALARY_COUNTER new_counter = {arr->salaries[i].salary, 1};
                    appendToSalariesCount(&salaries_count, &new_counter);
                }
            }
        }
 
        if(!region_found){
            printf("Modus: N/A\n");
            return true;
        }
    }
 
    size_t indexes[1000];
    size_t indexes_count = 0;
    findModusOfSalary(&salaries_count, indexes, &indexes_count);
 
    printf("Modus: ");
    if(indexes_count == 0){
        printf("%d ", salaries_count.data[indexes[0]].salary);
    }else{
        for(size_t i = 0; i < indexes_count; i++){
            printf("%d, ", salaries_count.data[indexes[i]].salary);
        }
        printf("%d ", salaries_count.data[indexes[indexes_count]].salary);
    }
    printf("[%ld]\n", salaries_count.data[indexes[0]].number_of_occurences);
 
    destroySalariesCount(&salaries_count);
    return true;
}
 
bool salaryController(SALARY_ARR * arr){
    char operation;
    int res;
    bool disable_loading_data = false;
 
    while((res = scanf("%c", &operation) != EOF)){
        if(res != 1)
            return false;
 
        switch(operation){
            case '+':
                if(disable_loading_data)
                    return false;
                if(!loadSalaries(arr))
                    return false;
                break;
            case '?':
                disable_loading_data = true;
                if(!getSalaryStatistics(arr))
                    return false;
                break;
            default:
                if(!isspace(operation))
                    return false;
                continue;
        }
    }
 
    return true;
}
 
int main(void){
    SALARY_ARR arr;
    initializeSalaryArr(&arr);
 
    printf("Data:\n");
    if(!salaryController(&arr)){
        printf("Nespravny vstup!\n");
        destroySalaryArr(&arr);
        return EXIT_FAILURE;
    }
 
    destroySalaryArr(&arr);
    return EXIT_SUCCESS;
}
