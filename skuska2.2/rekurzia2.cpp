#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct{
    int *spaces;
    char code[102];
    int len;
    int min, max;
    int count;
}code_t;

int isValid(const char *c){
    for (int i = 0; c[i] ; ++i) {
        if(!isdigit(c[i])){
            return 0;
        }
    }
    return 1;
}

int readInput(code_t *c){
    if(1!=scanf("%100s",c->code) || !isValid(c->code) || strlen(c->code) > 100){
        return 0;
    }
    c->len = (int)strlen(c->code);

    if(2!=scanf("%d %d",&c->min,&c->max) || c->min > c->max || c->min < 0 || c->max < 0){
        return 0;
    }

    return 1;
}


int isInRange(const char *buffer, code_t *c){
    int num;
    sscanf(buffer,"%d",&num);
    if(num < c->min || num > c->max){
        return 0;
    }
    return 1;
}

void genRec(code_t *c, int idx, int space){
    c->spaces[idx] = space;

    //terminating condition

    if(c->len-1 == idx){
        char *buffer = (char*)calloc(c->len*2,sizeof(char));
        for (int i = 0; i < c->len; ++i) {
            if(c->spaces[i]){
                if(!isInRange(buffer,c)){
                    free(buffer);
                    buffer = NULL;
                    return;
                }
                free(buffer);
                buffer = NULL;
                buffer = (char*)calloc(c->len*2,sizeof(char));
            }
            strncat(buffer,&c->code[i],1);
        }

        if(!isInRange(buffer,c)){
            free(buffer);
            buffer = NULL;
            return;
        }
        else{
            free(buffer);
            buffer = NULL;
        }

        for (int i = 0; i < c->len; ++i) {
            if(c->spaces[i]){
                printf(" ");
            }
            printf("%c",c->code[i]);
        }
        printf("\n");

        c->count++;

        return;
    }
    genRec(c,idx+1,0);
    genRec(c,idx+1,1);
}

int main(void){

    code_t c = {};

    if(!readInput(&c)){
        printf("Nespravny vstup.\n");
        return 1;
    }

    c.spaces = (int*)calloc(c.len,sizeof(int));
    genRec(&c,0,0);
    printf("Celkem: %d\n",c.count);

    free(c.spaces);
    return 0;
}
