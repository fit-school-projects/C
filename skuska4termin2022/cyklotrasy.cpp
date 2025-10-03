#include <stdio.h>
#include <stdlib.h>

typedef struct Tpoint {
    int m_Altitude;
    int m_Distance;
} TPOINT;

typedef struct Tdistance {
    int m_DisDifference;
    int m_AltDifference;
    TPOINT start;
    TPOINT end;
} TDIS;

int cmpInt(const void * a, const void * b)
{
    TDIS * aPtr = (TDIS*)a;
    TDIS * bPtr = (TDIS*)b;
    if (aPtr->m_AltDifference < bPtr->m_AltDifference)
        return 1;
    else if (aPtr->m_AltDifference > bPtr->m_AltDifference)
        return -1;
    if (aPtr->m_DisDifference < bPtr->m_DisDifference)
        return 1;
    else if (aPtr->m_DisDifference > bPtr->m_DisDifference)
        return -1;
    return 0;
}
int readInput(TPOINT ** points, int * sizePoints, int * maxSizePoints)
{
    int distance, altitude, res;
    scanf("%d", &altitude);
    
    (*points)[*sizePoints].m_Altitude = altitude;
    (*points)[*sizePoints].m_Distance = 0;
    (*sizePoints)++;

    while ( (res = ( scanf(" + %d %d", &distance, &altitude)) == 2)){
        if (*sizePoints >= *maxSizePoints){
            *maxSizePoints += *maxSizePoints / 2 + 10;
            *points = (TPOINT *) realloc (*points, *maxSizePoints * sizeof(**points));
        }
        (*points)[*sizePoints].m_Distance = distance;
        (*points)[*sizePoints].m_Altitude = altitude;
        (*sizePoints)++;
    }
    
    return 1;
}
int computeDistances(TDIS ** distances, TPOINT * points, int sizePoints, int * sizeDistances)
{
    int altDif = 0, disDif = 0;
    for (int i = 0; i < sizePoints; i++){
        for (int j = i + 1; j < sizePoints; j++){

            altDif = points[j].m_Altitude - points[i].m_Altitude;
            disDif = points[j].m_Distance - points[i].m_Distance;
            if (altDif <= 0){
                (*distances)[*sizeDistances].m_AltDifference = (altDif * -1);
                (*distances)[*sizeDistances].m_DisDifference = disDif;
                (*distances)[*sizeDistances].start = points[i];
                (*distances)[*sizeDistances].end = points[j];
                (*sizeDistances)++;
            }
        }
    }
    qsort(*distances, *sizeDistances, sizeof(**distances), (int(*)(const void *, const void *))cmpInt);
    
    return 1;
}

void printOutput(TDIS * distances, int sizeDistances)
{
    if(sizeDistances == 0){
        printf("Nenalezeno.\n");
        return;
    }
    int count = 0, maxDistance = distances[0].m_DisDifference;
    for (int i = 0; i < sizeDistances; i++){
        if (distances[i].m_DisDifference == maxDistance){
            count += 1;
        }
    }
    printf("%d km, klesani: %d m, varianty: %d\n", maxDistance, distances[0].m_AltDifference, count);
    for (int i = 0; i < count; i++){
        printf("+ %d (%d) -> + %d (%d)\n", distances[i].start.m_Distance, distances[i].start.m_Altitude, distances[i].end.m_Distance, distances[i].end.m_Altitude);
    }
}
int main ( void ){

    TPOINT * points = (TPOINT*) malloc (10 * sizeof(*points));
    TDIS * distances = (TDIS *) calloc (30000, sizeof(*points));
    int sizePoints = 0, maxSizePoints = 0, sizeDistances = 0;
    if (!readInput(&points, &sizePoints, &maxSizePoints)){
        free(points);
        printf("Nespravny vstup.\n");
        return 0;
    }
    computeDistances(&distances, points, sizePoints, &sizeDistances);
    printOutput(distances, sizeDistances);
    free(points);
    free(distances);
    return 0;
}
