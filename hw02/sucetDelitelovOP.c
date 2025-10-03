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
int sieveOfEratosthenes( char * sieve, int * primeNums, int n )
{ 
    int count = 0;
    for ( int i = 2; i < n; i++ )
        sieve[i] = 1;  
    sieve[0] = sieve[1] = 0; 
    for ( int i = 2; i < n; i++ )
    {
        if ( sieve[i] == 1 )
        {
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
int findSumOfOwnDivisors( int n, int * primeNums, char * sieve )
{
    int tmp = n;
    int result = 1;
    if (sieve[n] == 1)
        return 1;
    for(int i = 0; primeNums[i]*primeNums[i] <= n; i++){
        int currentPrimeNum = primeNums[i];
        if(tmp % currentPrimeNum== 0){
            int count = 1;
            while(tmp % currentPrimeNum == 0){
                tmp = tmp / currentPrimeNum;
                count += 1;
            }
            result *= (pow(currentPrimeNum, count) - 1) / (currentPrimeNum - 1);
        }
    }
    if(tmp > 1)
        result *= (pow(tmp, 2) - 1) / (tmp - 1);
    return result - n;
}
/**
 * @brief the function to calculate the number of prime sums
 * function will find the prime sum and raise the count by one
 * and then put this count to the array
 * if the number is not prime count is still the same and not raised
 * 
 * @param high 
 * @param primeNums 
 * @param sieve 
 * @return int* 
 */
int theOParray( int low, int high, int * primeNumsArr, char * sieve, int * count, int * OParr)
{
    int sum;
    for (int i = low+1; i <= high; i++)
    {
        sum = findSumOfOwnDivisors(i, primeNumsArr, sieve);
        if (sieve[sum] == 1) {
           (*count)++;
        }
        OParr[i] = *count;
    }
    return 0;
}
    

int main ( void )
{
    int low, high, n, tmp2 = 0, tmp1 = 0; 
    int count = 0;
    char query;
    int * OParr = NULL;
    char * sieve = NULL;
    int * primeNumsArr;
    int highestBefore = 1;
    
    /* array to store all the prime numbers, used when searching for dividers of the number n*/
    primeNumsArr = ( int *) malloc (2000000 * sizeof(*primeNumsArr));
    
    printf("Intervaly:\n");
    while ( (n = readInput(&low, &high, &query)) == 1 )
    {
        if (high < 3000 && tmp1 == 0 && tmp2 == 0) {
            free(sieve);
            sieve = (char *) malloc (10000 * sizeof(*sieve));
            OParr = (int *) calloc (3001, sizeof(*OParr));
            sieveOfEratosthenes(sieve, primeNumsArr, 10000);
            theOParray(highestBefore, 3000, primeNumsArr, sieve, &count, OParr);
            tmp1 = 1;
        }
        if (high > 3000 && tmp2 == 0) {
            free(sieve);
            free(OParr);
            sieve = (char *) malloc (17800000 * sizeof(*sieve));
            OParr = (int *) calloc (17800000, sizeof(*OParr));
            sieveOfEratosthenes(sieve, primeNumsArr, 17800000);
            tmp2 = 1;
        }
        if (tmp2 == 1 && highestBefore < high)
        {
            theOParray(highestBefore, high, primeNumsArr, sieve, &count, OParr);
            highestBefore = high;
        }
        
        if (query == '?')
        {
            for (int i = low; i <= high; i++)
            {
                if (OParr[i-1] < OParr[i])
                    printf("%d\n", i);
            }
        }
        printf("Celkem: %d\n", OParr[high] - OParr[low - 1]);
    }
   
    if ( n != EOF )
        printf("Nespravny vstup.\n");
    free(sieve);
    free(primeNumsArr);
    free(OParr);
    return 0;
}