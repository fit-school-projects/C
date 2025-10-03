#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

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
int primeNumbers( char * sieve, int * primeNums, int n )
{ 
    int count = 0;
    for ( int i = 2; i < n; i++ )
        sieve[i] = 1;  
    sieve[0] = sieve[1] = 0; 
    for ( int i = 2; i < n; i++ )
    {
        if ( sieve[i] == 1 )
        {
            // printf("%d ", i);
            primeNums[count] = i;
            count++;
            if (i <= sqrt(INT_MAX))
                for ( int j = i * i; j < n; j += i )
                    sieve[j] = 0; 
        }
    }
    return count;
}
/**
 * @brief function to find the sum of the divisors of the number n
 * @param n 
 * @return int returns the sum of the divisors of the number n 
 */
int findSumOfOwnDivisors( int n, int * primeNums, char * sieve, int * sumsOfNumbers)
{   
    if (sumsOfNumbers[n] != 0)
        return sumsOfNumbers[n];
    int tmp = n;
    int result = 1;
    if (sieve[n] == 1)
        return 1;
    for(int i = 0; primeNums[i]*primeNums[i] <= n; i++){
        if(tmp % primeNums[i] == 0){
            int count = 1;
            while(tmp % primeNums[i] == 0){
                tmp = tmp / primeNums[i];
                count += 1;
            }
            result *= (pow(primeNums[i], count) - 1) / (primeNums[i] - 1);
        }
    }
    if(tmp > 1)
        result *= (pow(tmp, 2) - 1) / (tmp - 1);
    sumsOfNumbers[n] = result - n;
    return result - n;
}

int main ( void )
{
    int low, high, n, sum;
    char query;
    char * sieve = NULL;
    int * sumsOfNumbers = NULL;
    int * primeNums;
    int tmp1 = 0, tmp2 = 0;
    
    
    primeNums = ( int *) malloc (2000000 * sizeof(*primeNums));
    
    printf("Intervaly:\n");
    while ( (n = readInput(&low, &high, &query)) == 1 )
    {
        if (high < 3000 && tmp1 == 0) {
            sieve = (char *) malloc (10000 * sizeof(*sieve));
            sumsOfNumbers = (int *) calloc (10000, sizeof(*sumsOfNumbers));
            primeNumbers(sieve, primeNums, 10000);
            tmp1 = 1;
        }
        if (high > 3000 && tmp2 == 0) {
            free(sieve);
            free(sumsOfNumbers);
            sieve = (char *) malloc (17800000 * sizeof(*sieve));
            sumsOfNumbers = (int *) calloc (17800000, sizeof(*sumsOfNumbers));
            primeNumbers(sieve, primeNums, 17800000);
            tmp2 = 1;
        }
        
        /* if the query is ? we are printing the numbers to the stdout*/
        int count = 0;
        for ( int i = low; i <= high; i++)
        {
            sum = findSumOfOwnDivisors(i, primeNums, sieve, sumsOfNumbers);
            // printf("sum: %d ", sum);
            if ( sieve[sum] == 1)
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
    free(sieve);
    free(primeNums);
    free(sumsOfNumbers);
    return 0;
}