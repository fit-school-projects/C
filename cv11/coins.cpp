#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int readCoins(int ** coins, int * sizeCoins, int * maxSizeCoins)
{
    int coin;
    while (scanf(" %d", &coin) == 1)
    {
        if (coin == 0) return 1;
        if (coin < 0) return 0;
        if (*sizeCoins >= *maxSizeCoins){
            *maxSizeCoins += *maxSizeCoins / 2 + 10;
            *coins = (int *) realloc (*coins, *maxSizeCoins * sizeof(**coins));
        }
        (*coins)[*sizeCoins] = coin;
        (*sizeCoins)++;
    }
    if (feof(stdin)){
        return 0;
    }

    return 1;
}

int findLeastAmountOfCoins(int * coins, int numOfCoins, int money)
{
    
 if (money == 0)
        return 0;
    int res = INT_MAX;
    for (int i = 0; i < numOfCoins; i++) {
        int sub;
        if (money >= coins[i]) {
            sub = 1 + findLeastAmountOfCoins(coins, numOfCoins, money - coins[i]);
            res = res < sub ? res : sub;
        }
    }
    
    if (res == INT_MAX || res < 0) 
        return -1;
    return res;
}
int main ( void )
{
    int sizeCoins = 0, maxSizeCoins = 10;
    int amount, res;
    int * coins = (int*) malloc (maxSizeCoins * sizeof(coins));

    printf("Mince:\n");
    if ( !readCoins(&coins, &sizeCoins, &maxSizeCoins) || sizeCoins == 0 ){
        printf("Nespravny vstup.\n");
        free(coins);
        return 1;
    }

    printf("Castky:\n");
    while ( scanf( " %d", &amount ) == 1){
        if (amount < 0){
            amount = -1;
            break;
        }
        res = findLeastAmountOfCoins(coins, sizeCoins, amount);
        if (res == -1) 
            printf("= nema reseni\n");
        else 
            printf("= %d\n", res);
    }
    
    if (!feof(stdin) || amount == -1){
        printf("Nespravny vstup.\n");
        free(coins);
        return 1;
    }

    free(coins);
    return 0;
}
