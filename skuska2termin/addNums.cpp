#ifndef __PROGTEST__
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct TItem {
    struct TItem * m_Next;
    char m_Digit;
} TITEM;
 
TITEM * createItem(char digit, TITEM * next) {
    TITEM *n = (TITEM *) malloc(sizeof(*n));
    n->m_Digit = digit;
    n->m_Next = next;
    return n;
}
 
void deleteList(TITEM * l) {
    while (l) {
        TITEM *tmp = l->m_Next;
        free(l);
        l = tmp;
    }
}
int listLength(TITEM * list)
{
    int count = 0;
    TITEM * tmp = list;
    while (tmp)
    {
        count++;
        tmp = tmp->m_Next;
    }
    return count;
}
void printList(TITEM * list)
{
    TITEM * tmp = list;
    printf("HEAD");
    while (tmp)
    {
        printf(" -> %c", tmp->m_Digit);
        tmp = tmp->m_Next;
    }
    printf("\n");
}
int validateList(TITEM * list)
{
    int length = listLength(list);
    if (list == NULL)
        return 0;
    TITEM * tmp = list;
    while (tmp){
        if (tmp->m_Digit - '0' < 0 || tmp->m_Digit - '0' > 9)
            return 0;
        tmp = tmp->m_Next;
    }
    tmp = list;

    while (tmp->m_Next != NULL){
        tmp = tmp->m_Next;
    }
    if (tmp->m_Digit - '0' == 0 && length > 1)
        return 0;

    return 1;
}

void pushBack(TITEM ** list, char digit)
{
    if (*list == NULL){
        *list = createItem(digit, *list);
        return;
    }
    TITEM * current = *list;
    while (current->m_Next != NULL){
        current = current->m_Next;
    }
    current->m_Next = createItem(digit, NULL);
}
#endif /* __PROGTEST__ */
TITEM * sumNumbers(TITEM * a, TITEM * b)
{
    TITEM * res = NULL;
    int sumOfTwoNumbers, remain = 0;
    while (a){
        if (b != NULL){
            sumOfTwoNumbers = (a->m_Digit - '0') + (b->m_Digit - '0') + remain;
            if (sumOfTwoNumbers > 9){
                sumOfTwoNumbers -= 10;
                remain = 1;
            }

            pushBack(&res, (sumOfTwoNumbers + '0'));
            a = a->m_Next;
            b = b->m_Next;
        } else {
            sumOfTwoNumbers = (a->m_Digit - '0') + remain;
            if (sumOfTwoNumbers > 9){
                sumOfTwoNumbers -= 10;
                remain = 1;
            }
            pushBack(&res, (sumOfTwoNumbers + '0'));
            a = a->m_Next;
        }
    }
    while (b){
        sumOfTwoNumbers = (b->m_Digit - '0') + remain;
            if (sumOfTwoNumbers > 9){
                sumOfTwoNumbers -= 10;
                remain = 1;
            }
            pushBack(&res, (sumOfTwoNumbers + '0'));
            b = b->m_Next;
    }
    if (remain){
        pushBack(&res, (remain + '0'));
    }
    return res;
}

TITEM * addList(TITEM * a, TITEM * b)
{
    TITEM * res;
    if (!validateList(a) || !validateList(b)){
        return NULL;
    }

    res = sumNumbers(a, b);
    return res;
}
 
#ifndef __PROGTEST__
 
int main(int argc, char *argv[]) {
    TITEM * a, * b, * res;

     
    a = createItem('3',
         createItem('4',
          createItem('5', NULL)));
    b = createItem('0', NULL);
    res = addList(a, b);
    assert (res->m_Digit == '3');
    assert (res->m_Next->m_Digit == '4');
    assert (res->m_Next->m_Next->m_Digit == '5');
    assert (res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);
 
    a = createItem('x', NULL);
    b = createItem('3', NULL);
    res = addList(a, b);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);
 
    a = createItem('5',
         createItem('0',
          createItem('0', NULL)));
    b = createItem('3', NULL);
    res = addList(a, b);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);

    a = createItem('2',
         createItem('3',
          createItem('9', NULL)));
    b = createItem('5',
         createItem('3',
          createItem('1', NULL)));
    res = addList(a, b);
    printList(res);
    assert (res->m_Digit == '7');
    assert (res->m_Next->m_Digit == '6');
    assert (res->m_Next->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Next->m_Digit == '1');
    assert (res->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('9',
         createItem('9',
          createItem ('9',
           createItem('9', NULL))));
    b = createItem('9',
         createItem('9',
          createItem('9', NULL)));
    res = addList(a, b);
    printList(res);
    
    deleteList(res);
    deleteList(a);
    deleteList(b);

    
    a = createItem('1', NULL);
    b = createItem('9',
         createItem('9',
          createItem('9', NULL)));
    res = addList(a, b);
    printList(res);
    
    deleteList(res);
    deleteList(a);
    deleteList(b);

    b = createItem('1', NULL);
    a = createItem('9',
         createItem('9',
          createItem('9', NULL)));
    res = addList(a, b);
    printList(res);
    
    deleteList(res);
    deleteList(a);
    deleteList(b);
    
    return 0;
}
 
#endif /* __PROGTEST__ */
