#include <stdio.h>
/**
 * @brief bonus test, when the number of digits of miliseconds is not the same
 * 
 * @param tmpMS1 
 * @param tmpMS2 
 * @param ms1 
 * @return int 
 */
int milisecondsConvert (int tmpMS1, int tmpMS2, int * ms1) 
{
    int numOfMiliSec;
    numOfMiliSec = tmpMS2 - tmpMS1;
    if (numOfMiliSec == 1)
    {
        *ms1 *= 100;
    } 
    else if (numOfMiliSec == 2) {
        *ms1 *= 10;
    }
    return *ms1; 
}
/**
 * @brief reads the stdin and takes care of the wrong input
 * 
 * @param h 
 * @param m 
 * @param s 
 * @param ms 
 * @param tmpMS1 
 * @param tmpMS2 
 * @return int 
 */
int readInput ( int * h, int * m, int * s, int * ms, int * tmpMS1, int * tmpMS2 ) 
{
    if ( scanf ( " %d : %d : %d , %n%d%n", h, m, s, tmpMS1, ms, tmpMS2 ) 
        != 4 
        || *h < 0
        || *h > 23
        || *m < 0
        || *m > 59
        || *s < 0
        || *s > 59
        || *ms < 0
        || *ms > 999
        )
    {
        return 1;
    }
    return 0;
}

int main () 
{
    int h1, m1, s1, ms1;
    int h2, m2, s2, ms2;
    // BONUS to know how much ms we have on input
    int tmpMS1, tmpMS2;

    printf("Zadejte cas t1:\n");
    if ( readInput(&h1, &m1, &s1, &ms1, &tmpMS1, &tmpMS2) == 1 )
    {
        printf ("Nespravny vstup.\n");
        return 1;
    };
    
    milisecondsConvert(tmpMS1, tmpMS2, &ms1);

    printf("Zadejte cas t2:\n");
    if ( readInput(&h2, &m2, &s2, &ms2, &tmpMS1, &tmpMS2) == 1 )
    {
        printf ("Nespravny vstup.\n");
        return 1;
    };

    milisecondsConvert(tmpMS1, tmpMS2, &ms2);

    int t1, t2;
    int h, m, s, ms;
    
    t1 = 60 * 60 * 1000 * h1 + 60 * 1000 * m1 + s1 * 1000 + ms1;
    t2 = 60 * 60 * 1000 * h2 + 60 * 1000 * m2 + s2 * 1000 + ms2; 
    if ( t1 <= t2 )
    {
        int t = t2 - t1;
        ms = (t % 1000);
        s = (t / 1000) % 60;
        m = (t / (1000 * 60)) % 60;
        h = (t / (1000 * 60 * 60)) % 24;
    } else {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Doba: %2d:%02d:%02d,%03d\n",h,m,s,ms);
    return 0;
}