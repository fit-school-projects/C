#include <stdio.h>
#include <stdlib.h>
#define max 2001

/**
 * @brief compare function for the quicksort
 * 
 * @param aPtr 
 * @param bPtr 
 * @return int 
 */
int intCmp(const int * aPtr, const int * bPtr)
{
    return (*bPtr < *aPtr) - (*aPtr < *bPtr);
}

/**
 * @brief finds the sums of the sequence and stores them into a new array
 * 
 * @param seqArr 
 * @param numbers 
 * @param arrayOfSums 
 * @return int returns the number of sums of the array
 */
int getSumsOfNumbers(int * seqArr, int * numbers, int * arrayOfSums)
{
    int position = 0;
    for (int i = 0; i < *numbers - 1; i++){
        int sum = seqArr[i];
        for (int j = i+1; j < *numbers; j++)
        {
            sum += seqArr[j]; 
            arrayOfSums[position] = sum;
            position++;
        }
    }
    return position;
}

/**
 * @brief function to compute the factorial
 * 
 * @param n 
 * @return int 
 */
int factorial( int n )
{
    int res = 1;
    for (int i = 0; i <= n; i++ ){
        res *= i;
    }
    return res;
}
/**
 * @brief function to compute the number of combinations
 * @param n 
 * @param k 
 * @return long long int 
 */
int binomialCoeficient(int n, int k)
{
    int tmp = 1;
    for (int i = 0; i < k; i++)
        tmp = tmp * (n - i) / (i + 1);
    return tmp;
}
/**
 * @brief function that finds the number of unique sums of the current sequence
 * 
 * @param arrayOfSums 
 * @param arrLength 
 * @return int 
 */
long long int numberOfCombinations( int * arrayOfSums, int arrLength )
{
    long long int numberOfPairs = 0;
    int position = 0;
    for (int i = 0; i < arrLength; i++){
        int count = 1;
        position++;
        while (arrayOfSums[i] == arrayOfSums[position])
        {
            count++;
            position++;
        }
        if (count > 1) {
            numberOfPairs += binomialCoeficient(count , 2);
        }
        i = position - 1;
    }
    return numberOfPairs;
}
/**
 * @brief function to read the numbers from the stdin
 * 
 * @param seqArr 
 * @param numberInTheSequence 
 * @param numbers 
 * @return int returns 1 when success
 */
int readInput( int * seqArr, int * numberInTheSequence, int * numbers )
{
    int res;
    if ((res = scanf(" %d", numberInTheSequence)) != 1){
       return res == EOF ? EOF : 0;
    }
    seqArr[*numbers] = *numberInTheSequence;
    (*numbers)++;
    return 1;
}

int main ( void )
{
    int n, numberInTheSequence, pos, numbers = 0;
    int sequenceArr[max];
    int * arrayOfSums;
    long long int sum;

    arrayOfSums = ( int * ) malloc (5000000 * sizeof(*arrayOfSums));
    printf("Posloupnost:\n");
    while ( (n = readInput(sequenceArr, &numberInTheSequence, &numbers)) == 1 ) {}
    if ( n != EOF || numbers == 0 || numbers > 2000) {
        free(arrayOfSums);
        printf("Nespravny vstup.\n");
        return 1;
    }
    pos = getSumsOfNumbers(sequenceArr, &numbers, arrayOfSums);
    qsort(arrayOfSums, pos, sizeof(arrayOfSums[0]), (int(*)(const void *, const void *))intCmp);
    sum = numberOfCombinations(arrayOfSums, pos);
    printf("Pocet dvojic: %lld\n", sum);
    free(arrayOfSums);
    return 0;
}
