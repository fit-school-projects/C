#include <stdio.h>
#include <math.h>

/**
 * @brief function to calculate the current interest of the money in the acount
 * 
 * @param bankStatus 
 * @param credit 
 * @param debit 
 * @return double 
 */
double interestCalculator ( double bankStatus, double credit, double debit )
{
    double interest;
    if ( bankStatus > 0 ) {
        interest = floorf(((bankStatus / 100) * credit) * 100) / 100;
    } else {
        interest = ceilf((( bankStatus / 100) * debit) * 100) / 100;
    }
    return interest;
}

int main ( void )
{
    double credit, debit, interest, bankStatus = 0;
    int input, day, amountOfMoney, prevDays, currentDay = 0;

    printf("Zadejte kreditni urok [%%]:\n");
    if ( scanf(" %lf", &credit) != 1 ){
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Zadejte debetni urok [%%]:\n");
    if ( scanf(" %lf", &debit) != 1 ){
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Zadejte transakce:\n");
    while ( (input = scanf( " %d , %d", &day, &amountOfMoney )) == 2) {
        if (day < currentDay || day < 0 ){
            printf("Nespravny vstup.\n");
            return 1;
        }
        /* previous day to know where to start counting the new interest
        current day is for the conditions (day can not be less than previous day)*/
        prevDays = currentDay;
        currentDay = day;
        
        /* condition when there are two different deposits in one day */
        if (day == prevDays && prevDays != 0){
            printf("Nespravny vstup.\n");
            return 1;
        }
        
        /* cycle which adds every day new amount of interest to the bank */
        for (int i = prevDays; i < currentDay; i++){
            interest = interestCalculator( bankStatus, credit, debit );
            bankStatus += interest;
        }
        /* new deposit is made */
        bankStatus += amountOfMoney;

        /* final print of the money left in the bank account*/
        if ( amountOfMoney == 0 ) {
            if (bankStatus > 0){
                bankStatus = ceilf(bankStatus*100) / 100;
            }
            else{
                bankStatus = floorf(bankStatus*100) / 100;
            }
            printf("Zustatek: %.2lf\n", bankStatus);
            return 0;
        }
    }
    /* condition if there is not 2 values in the while loop*/
    if ( input != 2 ){
        printf("Nespravny vstup.\n");
        return 1;
    }


    return 0;
}