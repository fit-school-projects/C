#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct TItem
{
    struct TItem * m_Next;
    int m_Mul;
    int m_Pow;
} TITEM;
 
TITEM * createItem ( int mul, int pow, TITEM * next )
{
    TITEM * n = (TITEM *) malloc (sizeof ( *n ));
    n -> m_Mul = mul;
    n -> m_Pow = pow;
    n -> m_Next = next;
    return n;
}
 
void deleteList (TITEM * l)
{
    while (l)
    {
        TITEM * tmp = l -> m_Next;
        free (l);
        l = tmp;
    }
}
#endif /* __PROGTEST__ */

int listLength(TITEM * list)
{
    int count = 0;
    TITEM * tmp = list;
    while (tmp){
        count++;
        tmp = tmp->m_Next;
    }
    return count;
}

void printList(TITEM * list)
{
    TITEM * tmp = list;
    printf("HEAD");
    while (tmp){
        printf(" -> %dx^%d", tmp->m_Mul, tmp->m_Pow);
        tmp = tmp->m_Next;
    }
    printf("\n");
}

int validatePoly(TITEM * list)
{
    int length = listLength(list) - 1;
    // empty list
    if (list == NULL) 
        return 0;
    // power is not ascending seq
    TITEM * tmp = list;
    while (length != 0){
        if ((tmp->m_Pow >= tmp->m_Next->m_Pow && tmp->m_Next != NULL) 
            || (tmp->m_Mul == 0 && tmp->m_Pow == 0 && tmp->m_Next != NULL))
            return 0;
        tmp = tmp->m_Next;
        length--;
    }
    return 1; 
}

void listPushBack(TITEM ** list, int mul, int pow)
{
    if (*list == NULL){
        *list = createItem(mul, pow, *list);
        return;
    }
    TITEM * current = *list;
    while (current->m_Next != NULL){
        current = current->m_Next;
    }
    current->m_Next = createItem(mul,pow,NULL);
}

TITEM * addPoly ( TITEM * a , TITEM * b )
{
    if ( !validatePoly(a) || !validatePoly(b) )
        return NULL;
    TITEM * res = NULL;
    if(a->m_Mul == 0 && a->m_Pow == 0)
        a = a->m_Next;
    if(b->m_Mul == 0 && b->m_Pow == 0)
        b = b->m_Next;
    while (a){
        if(b != NULL){
            if (a->m_Pow < b->m_Pow){   
                listPushBack(&res, a->m_Mul, a->m_Pow);
                a = a->m_Next;
            } 
            else if (a->m_Pow > b->m_Pow){
                listPushBack(&res, b->m_Mul, b->m_Pow);
                b = b->m_Next;
            } else {
                int mul = a->m_Mul + b->m_Mul;
                if (mul != 0)
                    listPushBack(&res, mul, a->m_Pow);
                a = a->m_Next;
                b = b->m_Next;
            }
        } else {
            listPushBack(&res, a->m_Mul, a->m_Pow);
            a = a->m_Next;
        }
    }
    while (b){
        listPushBack(&res, b->m_Mul, b->m_Pow);
        b = b->m_Next;
    }
    if (res == NULL){
        listPushBack(&res, 0, 0);
    }
    return res;
}
 
#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    TITEM * a, * b;
    TITEM * res;

    a = createItem (3,0,createItem (2,1,createItem (5,3,NULL)));
    b = createItem (-7,0,createItem (-2,1,createItem (-5,3,NULL)));
    res = addPoly(a,b);
    assert ( res -> m_Mul == -4 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (2,1,NULL);
    b = createItem (0,0,NULL);
    res = addPoly(a,b);
    assert ( res -> m_Mul == 2 );
    assert ( res -> m_Pow == 1 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
 
    a = createItem (2,1,NULL);
    b = createItem (3,1,createItem (4,2,createItem (2,3,createItem(1,0,NULL))));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
 
    a = createItem (2,1,NULL);
    b = createItem (3,1,createItem (4,1,NULL));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
 
    a = createItem (3,0,createItem (2,1,createItem (9,3,NULL)));
    b = createItem (0,0,createItem (4,2,createItem (-1,3,NULL)));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
    
    
    a = createItem (2,1,NULL);
    b = createItem (0,0,NULL);
    res = addPoly(a,b);
    assert ( res -> m_Mul == 2 );
    assert ( res -> m_Pow == 1 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (3,0,createItem (2,1,createItem (5,3,NULL)));
    b = createItem (-7,0,createItem (-2,1,createItem (-5,3,NULL)));
    res = addPoly(a,b);
    assert ( res -> m_Mul == -4 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
 
    a = createItem (3,1,createItem (-2,2,createItem (4,3,NULL)));
    b = createItem (-3,1,createItem (2,2,createItem (-4,3,NULL)));
    res = addPoly(a,b);
    assert ( res -> m_Mul == 0 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (3,0,createItem (2,1,createItem (9,3,NULL)));
    b = createItem (7,0,createItem (4,2,createItem (-1,3,NULL)));
    res = addPoly(a,b);
    printList(res);
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = NULL;
    b = createItem (7,0,createItem (4,2,createItem (-1,3,NULL)));
    res = addPoly(a,b);
    printList(res);
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
    
    return 0;
}
#endif /* __PROGTEST__ */
