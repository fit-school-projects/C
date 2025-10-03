#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#define MAX 7'500'000

/**
 * @brief reads the input from the stdin, ends with EOF
 * 
 * @param low lowest numberof the interval
 * @param high highest number of the interval
 * @param query the question mark or the # of the input query
 * @return int returns 1 if the output is good, or 0 if false
 */
int readInput(int * low, int * high, char * query)
{
    int res;
    if ( (res = scanf (" %c %d %d", query, low, high)) != 3 )
        return res == EOF ? EOF : 0;
    if ((*query != '?' && *query != '#') || *high < *low || *low < 1)
        return 0;
    return 1;
}
/**
 * @brief erathostens sieve, to fill the array with ones if the number is prime from the interval 2 to 7500000
 * TODO: effective work with the realloc to not call erathostenes every time we run the program with the high interval
 * @param arr array of ones and zeros : 1 number is prime
 * @param n 
 */
void primeNumbers(char * arr, int n)
{ 
    for ( int i = 2; i < n; i++ )
        arr[i] = 1;  
    arr[0] = arr[1] = 0; 
    for ( int i = 2; i < n; i++ )
    {
        if ( arr[i] == 1 )
        {
            // printf("%d ", i);
            if (i <= sqrt(INT_MAX))
                for ( int j = i * i; j < n; j += i )
                    arr[j] = 0; 
        }
    }
}
/**
 * @brief function to find the divisors of the number n
 * 
 * @param n 
 * @return int returns the sum of the divisors of the number n 
 */
int findSumOfOwnDivisors( char * arr, int n )
{
    int sum = 0;
    
    for (int i = 1; i <= sqrt(n); i++)
    {
        if (i == 1)
            sum++;
        else if (n % i == 0)
        {
            if (n / i == i) {
                sum += i;
            } else {
                sum += i + n / i;
            } 
        }
    }
    return sum;
}


int main ( void )
{
    int low, high, n, sum;
    char query;
    char * arrayOfPrimeNums; 
    
    arrayOfPrimeNums = (char *) malloc (20'000'000 * sizeof(*arrayOfPrimeNums));
    
    printf("Intervaly:\n");
    while ( (n = readInput(&low, &high, &query)) == 1 )
    {
        
        sum = findSumOfOwnDivisors(arrayOfPrimeNums, high);
        // printf("%d\n", sum);
        if (sum > 1000000)
            sum += 2500000;
        else {
            sum += 500000;
        }
        primeNumbers(arrayOfPrimeNums, sum); 
        
        int count = 0;
        
        /* if the query is ? we are printing the numbers to the stdout*/
        for ( int i = low; i <= high; i++)
        {
            sum = findSumOfOwnDivisors(arrayOfPrimeNums, i);
            // printf("sum: %d ", sum);
            if ( arrayOfPrimeNums[sum] == 1)
            {
                if (query == '?')
                    printf("%d\n", i);
                count++;
            }
        }
        printf("Celkem: %d\n", count);
    }
   
    if ( n != EOF )
        printf("Nespravny vstup.\n");
    free(arrayOfPrimeNums);
    return 0;
}