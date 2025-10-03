#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TItem
{
    struct TItem             * m_Next;
    char                     * m_Name;
    int                       m_Secret[24];
} TITEM;

#endif /* __PROGTEST__ */
/**
 * Function: newItem
 * -----------------
 * creates one item of the linked list TITEM
 * 
 * @param name 
 * @param next 
 * @return TITEM* 
 */
TITEM * newItem ( const char * name, TITEM * next, int secret) 
{
    TITEM * item = (TITEM*) malloc (sizeof(*item));
    item->m_Name = strdup(name);
    item->m_Secret[0] = secret;
    item->m_Next = next;
    return item;
}

/**
 * Function: pushItem
 * ------------------
 * adds one item to the front of the linked list TITEM
 * 
 * @param list 
 * @param item 
 * @return TITEM** 
 */
TITEM ** pushItem (TITEM ** list, TITEM *item) {
    if (!item) 
        return list;
    item->m_Next = *list;
    *list = item;
    return list;
}

/**
 * Function: popFirstItem
 * ----------------------
 * removes the first item of the linked list TITEM
 * 
 * @param list 
 * @return TITEM* 
 */
TITEM * popFirstItem (TITEM ** list) {
    TITEM * tmp = *list;
    if ( *list == NULL ) 
        return NULL;

    *list = tmp->m_Next;
    tmp->m_Next = NULL;
    return tmp;
}

/**
 * Function: freeList
 * ------------------
 * frees items in the linked list TITEM
 * 
 * @param src pointer to the first item of the linked list
 */
void freeList(TITEM * src) {
    while (src)
    {
        TITEM * tmp = src->m_Next;
        free(src->m_Name);
        free(src);
        src = tmp;
    }
}

/**
 * Function: reverseList
 * ---------------------
 * reverse the items of the linked list
 * used in the recursive merge sort implementation 
 * 
 * @param list linked list
 */
void reverse(TITEM ** list) {
    TITEM * tmp = NULL;
    while ( *list ){
        pushItem(&tmp, popFirstItem(list));
    }
    *list = tmp;
}

/**
 * Function: listCount
 * -------------------
 * function to calculate the length of the linked list
 * 
 * @param head pointer to the first item of the linked list
 * @return returns 0 if the length of the linked list is less or equal to one or 1 if otherwise 
 */
size_t listCount(TITEM * head)
{
    size_t count = 0;
    TITEM * current = head;
    while (current != NULL)
    {
        count++;
        current = current->m_Next;
    }
    if (count <= 1) return 0;
    return 1;
}

/**
 * Function: listSplit
 * -------------------
 * splits the linked list into two halves and returns one side of the splitted linked list - tmp, 
 * the other side is the original linked list - list
 * 
 * @param list 
 * @return TITEM* 
 */
TITEM * listSplit (TITEM ** list) 
{
    TITEM * tmp = NULL;
    while (*list) {
        list = &(*list)->m_Next;
        pushItem(&tmp, popFirstItem(list));
    }
    return tmp;
}

/**
 * Function: listMerge
 * -------------------
 * function which merges the left and right side (linked list) into one
 * compares names in order given by the param ascending
 * 
 * @param rightSide 
 * @param leftSide 
 * @param ascending 
 * @return TITEM* 
 */
TITEM * listMerge (TITEM ** rightSide, TITEM ** leftSide, int ascending) {
    TITEM *tmp = NULL;

    while (*rightSide != NULL && *leftSide != NULL){
        if (ascending){
            pushItem(&tmp, popFirstItem(strcmp((*rightSide)->m_Name, (*leftSide)->m_Name) < 0 ? rightSide : leftSide));
        } else {
            pushItem(&tmp, popFirstItem(strcmp((*rightSide)->m_Name, (*leftSide)->m_Name) > 0 ? rightSide : leftSide));
        }
    }

    while (*rightSide) 
        pushItem(&tmp, popFirstItem(rightSide));
    while (*leftSide) 
        pushItem(&tmp, popFirstItem(leftSide));

    reverse(&tmp);
    return tmp;
}
/**
 * Function: mergeSort
 * -------------------
 * implements the merge sort algorithm recursively
 * 
 * @param list 
 * @param asc 
 */
void mergeSort(TITEM ** list, int asc) {

    if (!listCount(*list))
        return;

    TITEM * tmp = listSplit (list);
    mergeSort(&tmp, asc);
    mergeSort(list, asc);
    *list = listMerge(&tmp, list, asc);
}
/**
 * Function: sortList
 * ------------------
 * sorts the linked list in the order given
 * when ascending is 1 - upwardly, 0 - downwardly 
 * 
 * @param l 
 * @param ascending 
 * @return TITEM* 
 */
TITEM * sortList ( TITEM * l, int ascending )
{
    mergeSort(&l, ascending);
    return l;
}

void printList(TITEM * head)
{
    TITEM * current = head;
    printf("Head");
    while (current != NULL)
    {
        printf(" -> %s %d", current->m_Name, current->m_Secret[0]);
        current = current->m_Next;
    }
    printf("\n");
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  TITEM * l;
  // char tmp[50];

  // assert ( sizeof ( TITEM ) == sizeof ( TITEM * ) + sizeof ( char * ) + 24 * sizeof ( char ) );
  l = NULL;
  l = newItem ( "aaa", l, 1 );
  l = newItem ( "aaa", l, 2 );
  l = newItem ( "aaa", l, 3 );
  l = newItem ( "aaa", l, 4 );
  l = newItem ( "aaa", l, 5 );
  printList(l);
  l = sortList(l,1);
  printList(l);
  l = sortList(l,0);
  printList(l);
  freeList(l);
  
  /*
  l = NULL;
  l = newItem ( "PA1", l );
  l = newItem ( "PA2", l );
  l = newItem ( "UOS", l );
  l = newItem ( "LIN", l );
  l = newItem ( "AG1", l );
  
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  
  l = sortList ( l, 1 );
  
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = newItem ( "programming and algorithmic I", l );
  l = newItem ( "AAG", l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AAG" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "programming and algorithmic I" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );

  l = sortList ( l, 0 );
  assert ( l
           && ! strcmp ( l -> m_Name, "programming and algorithmic I" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AAG" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeList ( l );
  l = NULL;
  strncpy ( tmp, "PA1", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "PA2", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "UOS", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "LIN", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "AG1", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortList ( l, 1 );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  strncpy ( tmp, "programming and algorithmic I", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "AAG", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AAG" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "programming and algorithmic I" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortList ( l, 0 );
  assert ( l
           && ! strcmp ( l -> m_Name, "programming and algorithmic I" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AAG" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeList ( l );
  */
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
