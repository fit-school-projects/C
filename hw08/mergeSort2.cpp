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

int cmpName ( const TITEM * a,
              const TITEM * b )
{
  return strcmp ( a -> m_Name, b -> m_Name );
}

int cmpNameInsensitive ( const TITEM * a,
                         const TITEM * b )
{
  return strcasecmp ( a -> m_Name, b -> m_Name );
}

int cmpNameLen ( const TITEM * a,
                 const TITEM * b )
{
  size_t la = strlen ( a -> m_Name ), lb = strlen ( b -> m_Name );
  return ( lb < la ) - ( la < lb );
}
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
    int length = strlen(name);
    TITEM * item = (TITEM*) malloc (sizeof(*item));
    item->m_Name = (char*) malloc ((length+1) * sizeof(char));
    strcpy(item->m_Name, name);
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
TITEM * listMerge (TITEM * rightSide, TITEM * leftSide, int ascending, int (* cmpFn) ( const TITEM *, const TITEM *)) {
    if (rightSide == NULL){
        return leftSide;
    }
    if (leftSide == NULL){
        return rightSide;
    }
    TITEM * tmp;
    if (cmpFn(rightSide,leftSide) > 0 || (cmpFn(rightSide,leftSide) == 0 && strcmp(rightSide->m_Name,leftSide->m_Name) > 0)){
        tmp = rightSide;
        tmp->m_Next = listMerge(rightSide->m_Next, leftSide, ascending, cmpFn);
    } else {
        tmp = leftSide;
        tmp->m_Next = listMerge(rightSide, leftSide->m_Next, ascending, cmpFn);
    }
    
    return tmp;
}

TITEM * midPoint (TITEM * head){
    TITEM * slow = head;
    TITEM * fast = head->m_Next;

    while (fast != NULL && fast->m_Next != NULL){
        slow = slow->m_Next;
        fast = fast->m_Next->m_Next;
    }
    return slow;
}
/**
 * Function: mergeSort
 * -------------------
 * implements the merge sort algorithm recursively
 * 
 * @param list 
 * @param asc 
 */
TITEM * mergeSort(TITEM * list, int asc, int (* cmpFn) ( const TITEM *, const TITEM *))
{
    if (list == NULL || list->m_Next == NULL){
        return list;
    }
    TITEM * middle = midPoint(list);

    TITEM * a = list;
    TITEM * b = middle->m_Next;
    middle->m_Next = NULL;

    a = mergeSort(a, asc, cmpFn);
    b = mergeSort(b, asc, cmpFn);

    return listMerge(a,b, asc, cmpFn);

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
TITEM * sortListCmp ( TITEM  * l, int ascending, int (* cmpFn) ( const TITEM *, const TITEM *) )
{
    l = mergeSort(l, ascending, cmpFn);
    if (ascending){
        reverse(&l);
    }
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
  l = sortListCmp(l,1,cmpName);
  printList(l);
  l = sortListCmp(l,0,cmpName);
  printList(l);

  /*
  l = NULL;
  l = newItem ( "BI-PA1", l );
  l = newItem ( "BIE-PA2", l );
  l = newItem ( "NI-PAR", l );
  l = newItem ( "lin", l );
  l = newItem ( "AG1", l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortListCmp ( l, 1, cmpName );
  printList(l);
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortListCmp ( l, 1, cmpNameInsensitive );
  printList(l);
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortListCmp ( l, 1, cmpNameLen );
  printList(l);
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = newItem ( "AAG.3", l );
  printList(l);
  assert ( l
           && ! strcmp ( l -> m_Name, "AAG.3" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortListCmp ( l, 0, cmpNameLen );
  printList(l);
  assert ( l
           && ! strcmp ( l -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "AAG.3" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeList ( l );
  l = NULL;
  strncpy ( tmp, "BI-PA1", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "BIE-PA2", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "NI-PAR", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "lin", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "AG1", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortListCmp ( l, 1, cmpName );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortListCmp ( l, 1, cmpNameInsensitive );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortListCmp ( l, 1, cmpNameLen );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  strncpy ( tmp, "AAG.3", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AAG.3" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortListCmp ( l, 0, cmpNameLen );
  assert ( l
           && ! strcmp ( l -> m_Name, "BIE-PA2" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "AAG.3" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeList ( l );
  */
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
