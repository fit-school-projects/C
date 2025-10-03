#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct TItem
{
  struct TItem * m_Next;
  struct TItem * m_Prev;
  int      m_Val;
} TITEM;

typedef struct TData
{
  TITEM * m_First;
  TITEM * m_Last;
} TDATA;

#endif /* __PROGTEST__ */

int lengthList ( TDATA * l )
{
    TITEM * x = l->m_First;
    int count = 0;
    while (x != NULL)
    {
        count++;
        x = x->m_Next;
    }
    return count;
}

void insertStart ( TDATA * l, int x )
{
    TITEM * item = (TITEM*) malloc (sizeof(*item));
    item->m_Val = x;
    item->m_Next = l->m_First;
    item->m_Prev = NULL;
    
    if (l->m_First != NULL){
        l->m_First->m_Prev = item;
    }
    l->m_First = item;
    if (l->m_Last == NULL)
        l->m_Last = item;
}

void insertEnd   ( TDATA * l, int x )
{
    TITEM * item = (TITEM*) malloc (sizeof(*item));
    item->m_Val = x;
    item->m_Next = NULL;
    item->m_Prev = l->m_Last;

    if (l->m_Last)
        l->m_Last->m_Next = item;
    else
        l->m_First = item;
    l->m_Last = item;
}

int findMax (TDATA * l)
{
    TITEM * x = l->m_First;
    int max = x->m_Val;
    while (x != NULL)
    {
        if (x->m_Val > max)
        {
            max = x->m_Val;
        }
        x = x->m_Next;
    }
    return max;
}

TITEM * nodeDelete ( TITEM * item ) {
    TITEM * next = item->m_Next; 
    free (item);
    return next;
}

int removeMax ( TDATA * l )
{
    if ( l->m_First == NULL && l->m_Last == NULL )
        return 0;
    int max = findMax(l);
    int length = lengthList(l);
    TITEM * current = l->m_First; 
    int removedCount = 0;

    while (current != NULL)
    {
        if (current->m_Val != max){
            current = current->m_Next;
            continue;
        }
        length--;
        removedCount++;
        if (current == l->m_First)
            l->m_First = current->m_Next;
        if (current == l->m_Last)
            l->m_Last = current->m_Prev;
        if (current->m_Prev != NULL)
            current->m_Prev->m_Next = current->m_Next;
        if (current->m_Next != NULL)
            current->m_Next->m_Prev = current->m_Prev;
        current = nodeDelete(current);
    }
    if (length == 0){
        l->m_First = l->m_Last = NULL;
    }
    return removedCount;
}

void destroyAll  ( TDATA * l )
{
    TITEM * x = l->m_First;
    while (x != NULL)
    {
        TITEM * tmp = x->m_Next;
        free(x);
        x = tmp;
    }
    l->m_First = l->m_Last = NULL;
}

#ifndef __PROGTEST__
int main ( void )
{
  /*
  TDATA a;
  a . m_First = a . m_Last = NULL;
  insertEnd ( &a, 1 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 1 );
  insertEnd ( &a, 3 );
  insertEnd ( &a, 4 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 5 );
  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 1
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Prev == NULL
           && a . m_First -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Prev == a . m_First
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 4
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 5
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( removeMax ( &a ) == 1 );
  
  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 1
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Prev == NULL
           && a . m_First -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Prev == a . m_First
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 4
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  destroyAll ( &a );

  a . m_First = a . m_Last = NULL;
  insertEnd ( &a, 1 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 3 );
  insertEnd ( &a, 0 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 3 );
  insertStart ( &a, 1 );
  insertStart ( &a, 2 );
  insertStart ( &a, 3 );
  
  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 3
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Prev == NULL
           && a . m_First -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Prev == a . m_First
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 0
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( removeMax ( &a ) == 3 );
  
  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 2
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Prev == NULL
           && a . m_First -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Prev == a . m_First
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 0
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( removeMax ( &a ) == 3 );
  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 1
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Prev == NULL
           && a . m_First -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Prev == a . m_First
           && a . m_First -> m_Next -> m_Next -> m_Val == 0
           && a . m_First -> m_Next -> m_Next -> m_Next == NULL
           && a . m_First -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next
           && a . m_Last == a . m_First -> m_Next -> m_Next );
  assert ( removeMax ( &a ) == 2 );
  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 0
           && a . m_First -> m_Next == NULL
           && a . m_First -> m_Prev == NULL
           && a . m_Last == a . m_First );
  destroyAll ( &a );

  a . m_First = a . m_Last = NULL;
  insertEnd ( &a, -1 );
  insertEnd ( &a, -2 );
  insertEnd ( &a, -10000 );
  insertEnd ( &a, -1 );
  insertEnd ( &a, -300 );
  assert ( removeMax ( &a ) == 2 );
  assert ( a . m_First != NULL
           && a . m_First -> m_Val == -2
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Prev == NULL
           && a . m_First -> m_Next -> m_Val == -10000
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Prev == a . m_First
           && a . m_First -> m_Next -> m_Next -> m_Val == -300
           && a . m_First -> m_Next -> m_Next -> m_Next == NULL
           && a . m_First -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next
           && a . m_Last == a . m_First -> m_Next -> m_Next );
  destroyAll ( &a );
  */
  return 0;
}
#endif /* __PROGTEST__ */
