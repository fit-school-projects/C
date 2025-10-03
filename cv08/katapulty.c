#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct TTargets
{
    double m_X;
    double m_Y;
} TTARG;

typedef struct TRadars
{
    double m_X;
    double m_Y;
    double m_Radius;
} TRAD;

void loadTarget (TTARG ** targets, int * maxSizeTargets, int * sizeTargets, double target_x, double target_y)
{
    if (*sizeTargets >= *maxSizeTargets)
    {
        *maxSizeTargets += (*maxSizeTargets / 2 + 10);
        *targets = (TTARG*) realloc (*targets, *maxSizeTargets * sizeof(**targets));
    }
    (*targets)[*sizeTargets].m_X = target_x;
    (*targets)[*sizeTargets].m_Y = target_y;
    (*sizeTargets)++;
}

void loadRadar (TRAD ** radars, int * maxSizeRadars, int * sizeRadars, double radar_x, double radar_y, double radar_radius)
{
    if (*sizeRadars >= *maxSizeRadars)
    {
        *maxSizeRadars += *maxSizeRadars / 2 + 10;
        *radars = (TRAD*) realloc (*radars, *maxSizeRadars * sizeof(**radars));
    }
    (*radars)[*sizeRadars].m_X = radar_x;
    (*radars)[*sizeRadars].m_Y = radar_y;
    (*radars)[*sizeRadars].m_Radius = radar_radius;
    (*sizeRadars)++;
}

double distanceBetweenTwoPoints(double radar_x, double radar_y, double target_x, double target_y)
{
    double distance = sqrt((target_x - radar_x)*(target_x - radar_x) + (target_y - radar_y)*(target_y - radar_y));
    return distance;
}

void findCoverage(TRAD ** radars, TTARG ** targets, int * sizeRadars, int * sizeTargets)
{
    int numOfRadars = 0;
    double distance;
    while(numOfRadars != *sizeRadars)
    {
        int countOfTargets = 0;
        for (int i = 0; i < *sizeTargets; i++)
        {
            distance = distanceBetweenTwoPoints((*radars)[numOfRadars].m_X, (*radars)[numOfRadars].m_Y, (*targets)[i].m_X, (*targets)[i].m_Y);
            if (((fabs((*radars)[numOfRadars].m_Radius - distance) <= 1000 * __DBL_EPSILON__ * (*radars)[numOfRadars].m_Radius)) || ((*radars)[numOfRadars].m_Radius > distance)){
                countOfTargets++;
            }
        }
        printf("Radar #%d: %d\n", numOfRadars, countOfTargets);
        numOfRadars++;
    }
}

int main ( void )
{
    int res, maxSizeTargets = 10, maxSizeRadars = 10, sizeTargets = 0, sizeRadars = 0;
    double radar_x, radar_y, target_x, target_y, radar_radius;
    char letter;
    int n = 0;

    TRAD * radars = (TRAD*) malloc (maxSizeRadars * sizeof(*radars));
    TTARG * targets = (TTARG*) malloc (maxSizeTargets * sizeof(*targets));

    printf("Seznam cilu a radaru:\n");
    while ((res = scanf(" %c", &letter)) == 1)
    {
        if (letter == 'T')
            if ( scanf (" %lf %lf", &target_x, &target_y ) != 2 ){
                n = 1;
                break;
            }
                
        if (letter == 'R') 
            if ( scanf (" %lf %lf %lf", &radar_x, &radar_y, &radar_radius) != 3 || radar_radius <= 0)
            {
                n = 1;
                break;
            }
        if (letter != 'T' && letter != 'R')
            {
                n = 1;
                break;
            }
         switch (letter)
        {
        case 'T':
            loadTarget(&targets, &maxSizeTargets, &sizeTargets, target_x, target_y);
            break;
        case 'R':
            loadRadar(&radars, &maxSizeRadars, &sizeRadars, radar_x, radar_y, radar_radius);
            break;
        }
    }

    if (!feof(stdin) || n == 1) {
        printf("Nespravny vstup.\n");
        free(radars);
        free(targets);
        return 1;
    }
    printf("Pokryti:\n");
    findCoverage(&radars, &targets, &sizeRadars, &sizeTargets);
    free(radars);
    free(targets);
    return 0;
}
