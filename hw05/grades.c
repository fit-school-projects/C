#include <stdio.h>
#include <stdlib.h>

#define ARRAY_EXPAND_ADD 4
#define ARRAY_EXPAND_MULTIPLIER 2

typedef struct Tarray {
    int * m_Data;
    int   m_Capacity;
    int   m_Size;
} TARRAY;

/**
 * Function: intCmp
 * ----------------
 * Compares two integer values
 * 
 * @param[out] aPtr 
 * @param[out] bPtr 
 * @returns int 
 */
int intCmp( const int * aPtr, const int * bPtr )
{
    return ( *bPtr < *aPtr ) - ( *aPtr < *bPtr );
}

/**
 * Function: readGrades
 * --------------------
 * Reads the grades of the students from the stdin and stores them into array
 * 
 * Reading is not successful:
 * if openBracket is missing or is not '{'
 * if grade is not a valid integer or grade is less then 0 or greater than 1000000000
 * if separator between grades is not ',' or there is no '}' after the last number
 * 
 * @param[out] array array of grades 
 * @returns 1 if reading is successful, 0 otherwise
 */
int readGrades( TARRAY * array )
{
    int grade; 
    char separator, openBracket;

    printf("Pocty bodu:\n");
    if ( scanf( " %c ", &openBracket ) != 1 
        || openBracket != '{' )
    {
        return 0;
    }

    while ( 1 )
    {
        if ( scanf( "%d %c ", &grade, &separator ) != 2 
            || grade < 0 
            || grade > 1000000000 
            || ( separator != ',' && separator != '}' ) )
        {
            return 0;
        }

        if ( array->m_Size >= array->m_Capacity )
        {
            array->m_Capacity += array->m_Capacity / ARRAY_EXPAND_MULTIPLIER + ARRAY_EXPAND_ADD;
            array->m_Data = ( int * ) realloc ( array->m_Data, array->m_Capacity * sizeof(int) );
        }
        array->m_Data[ array->m_Size ] = grade;
        array->m_Size++;

        if ( separator == '}' )
            break;
    }
    
    return 1;
}

/**
 * Function readInterval
 * ---------------------
 * Reads the interval of the grades in the format ( from ; to )
 * 
 * Reading is not successful:
 * if startOfTheIntervalBracket is missing or is not '(' or '<'
 * if endOfTheIntervalBracket is missing or is not ')' or '>'
 * 
 * @param[out] from the beginnig number of the interval 
 * @param[out] to the ending number of the interval
 * @return 1 if reading is successful, EOF if EOF and 0 if the reading is not successful 
 */
int readInterval( int * from, int * to )
{
    int res;
    char startOfTheIntervalBracket, endOfTheIntervalBracket;

    if ( ( res = scanf( " %c %d ; %d %c ", &startOfTheIntervalBracket, from, to, &endOfTheIntervalBracket ) ) != 4 )
    {
        return res == EOF ? EOF : 0;
    }

    if ( ( startOfTheIntervalBracket != '(' && startOfTheIntervalBracket != '<' ) 
        || ( endOfTheIntervalBracket != ')' && endOfTheIntervalBracket != '>' ) )
    {
        return 0;
    }
    /* When the startOfTheIntervalBracket and endOfTheIntervalBracket are open we */
    /* want to work with the last number which is still in the range we want grades from, */
    /* so we increase/decrese from/to parameters by one */
    if (startOfTheIntervalBracket == '(')
        ( *from )++;
    if (endOfTheIntervalBracket == ')')
        ( *to )--;

    return 1;
}

/**
 * Function calculateStudents
 * --------------------------
 * Calculates the number of students with the grades from the given interval < from ; to >
 * 
 * @param[out] array sorted array with the grades of students 
 * @param[in] from   first grade of the interval
 * @param[in] to     last grade of the interval
 * @returns the number of students which have grades that belongs to the given interval
 */
int calculateStudents(TARRAY * array, int from, int to)
{
    int positionInTheArray = 0;
    int students = 0;

    /* We cycle through the sorted array of grades while we hit the beginning number of the interval (from parameter) */
    /* when the beginning number of the interval is negative, we are starting automatically from 0 */
    while ( array->m_Data[ positionInTheArray ] < from && positionInTheArray != array->m_Size && from >= 0 )
    {
        positionInTheArray++;
    }

    /* When the "to" parameter is greater than the largest number in the array we automatically gets the number of students */
    /* by subtracting the position from the size of the sorted array of numbers */
    if ( to >= array->m_Data[ array->m_Size - 1 ] )
    {
        students = array->m_Size - positionInTheArray;
        return students;
    }

    /* We cycle through the sorted array of grades while we hit the first number greater than "to" (the end of the interval) */
    /* When we find the number that belongs to the interval <from;to>, we increase the number of students by one */
    while ( ( array->m_Data[ positionInTheArray ] < to + 1 ) && positionInTheArray != array->m_Size )
    {
        students++;
        positionInTheArray++;
    }

    return students;
}

int main ( void ) {

    TARRAY array = { NULL, 0, 0 };
    int from, to, res, students;

    if ( !readGrades( &array ) )
    {
        printf("Nespravny vstup.\n");
        free(array.m_Data);
        return EXIT_FAILURE;
    }
    
    qsort( array.m_Data, array.m_Size, sizeof( array.m_Data[ 0 ] ), ( int(*)( const void *, const void * ) )intCmp );

    printf( "Intervaly:\n" );
    while ( ( res = readInterval( &from, &to ) ) == 1 )
    {
        students = calculateStudents( &array, from, to );
        printf( " -> %d\n", students );
    }

    if ( res != EOF )
    {
        printf( "Nespravny vstup.\n" );
        free( array.m_Data );
        return EXIT_FAILURE;
    }
    
    free( array.m_Data );
    return EXIT_SUCCESS;
}
