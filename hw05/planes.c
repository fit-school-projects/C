#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_NAME_LENGTH 200

typedef struct Tplanes
{
    double m_X;
    double m_Y;
    char   m_Name[MAX_NAME_LENGTH];
} TPLANE;

typedef struct TplanePairs
{
    double m_Distance;
    char   m_Plane1[MAX_NAME_LENGTH];
    char   m_Plane2[MAX_NAME_LENGTH];
} TPAIR;

/**
 * @brief function that sorts all plane pairs by the distance between them from lowest to highest
 * @param a 
 * @param b 
 * @return int 
 */
int cmpDistance(const void * a, const void * b)
{
    TPAIR * aPtr = (TPAIR*)a;
    TPAIR * bPtr = (TPAIR*)b;

    if(aPtr->m_Distance > bPtr->m_Distance)
        return 1;
    else if(aPtr->m_Distance < bPtr->m_Distance)
        return -1;
    return 0;
}
/**
 * @brief function that calculates the distance between two planes
 * @param plane1_x 
 * @param plane1_y 
 * @param plane2_x 
 * @param plane2_y 
 * @return double 
 */
double distanceBetweenTwoPlanes(double plane1_x, double plane1_y, double plane2_x, double plane2_y)
{
    double distance = sqrt((plane2_x - plane1_x)*(plane2_x - plane1_x) + (plane2_y - plane1_y)*(plane2_y - plane1_y));
    return distance;
}

/**
 * @brief function which counts the distance between the current plane and all the previuos ones and save the planePairs with their distance
 * to the strcture planePairs
 * @param planePairs 
 * @param planes 
 * @param numOfPlanes 
 * @param planePairsMaxSize 
 * @param planePairsSize 
 * @param minDistance 
 * @param count 
 */
void findPlanePairsWithShortestDistance(TPAIR ** planePairs, TPLANE ** planes, int * numOfPlanes, int * planePairsMaxSize, int * planePairsSize, double * minDistance, int * count)
{
    double distance;
    for (int i = 0; i < (*numOfPlanes)-1; i++)
    {
        distance = distanceBetweenTwoPlanes((*planes)[i].m_X, (*planes)[i].m_Y,(*planes)[(*numOfPlanes)-1].m_X,(*planes)[(*numOfPlanes)-1].m_Y );
        if ((*minDistance > distance) && !(fabs(distance - *minDistance) <= 1000 * __DBL_EPSILON__ * *minDistance)){
            *minDistance = distance;
            *count = 0;
        }
        if (fabs(distance - *minDistance) <= 1000 * __DBL_EPSILON__ * *minDistance)
        {
            if (*planePairsSize >= *planePairsMaxSize)
            {
                *planePairsMaxSize += *planePairsMaxSize / 2 + 10;
                *planePairs = (TPAIR*) realloc (*planePairs, *planePairsMaxSize * sizeof(**planePairs));
            }
            (*planePairs)[*planePairsSize].m_Distance = distance;
            strncpy((*planePairs)[*planePairsSize].m_Plane1, (*planes)[i].m_Name, sizeof((*planes)[i].m_Name));
            strncpy((*planePairs)[*planePairsSize].m_Plane2, (*planes)[(*numOfPlanes)-1].m_Name, sizeof((*planes)[i].m_Name));
            (*planePairsSize)++;
            (*count)++;
        }
    }
}
/**
 * @brief function which collects the data from the stdin and puts them into the structure of planes with their x and y coordinates and names
 * @param planes 
 * @param planePairs 
 * @param planesSize 
 * @param planesMaxSize 
 * @param planePairsSize 
 * @param planePairsMaxSize 
 * @param minDistance 
 * @param count 
 * @return int 
 */
int readInput(TPLANE ** planes, TPAIR ** planePairs, int * planesSize, int * planesMaxSize, int * planePairsSize, int * planePairsMaxSize, double * minDistance, int * count)
{
    double x, y, n;
    char name[MAX_NAME_LENGTH];
    printf("Pozice letadel:\n");
    while ((n = scanf(" %lf , %lf : %199s", &x, &y, name)) == 3){
        if (*planesSize >= *planesMaxSize)
        {
            *planesMaxSize += *planesMaxSize / 2 + 10;
            *planes = (TPLANE*) realloc (*planes, *planesMaxSize * sizeof(**planes));
        }
        (*planes)[*planesSize].m_X = x;
        (*planes)[*planesSize].m_Y = y;
        strncpy((*planes)[*planesSize].m_Name, name, sizeof(name));
        (*planesSize)++;
        //
        findPlanePairsWithShortestDistance( planePairs, planes, planesSize, planePairsMaxSize, planePairsSize, minDistance, count);
    }
    
    if (!feof(stdin)){
        return 0;
    }
    return 1;
}
/**
 * @brief function which sorts the structure of all the distances and prints only the ones with the min distance to the stdout
 * @param planePairs 
 * @param numOfPlanesPairs 
 * @param minDistance 
 * @param countMin 
 */
void printOutput(TPAIR ** planePairs, int * numOfPlanesPairs, double * minDistance, int * countMin)
{
    printf("Vzdalenost nejblizsich letadel: %lf\n", *minDistance);
    qsort(*planePairs, *numOfPlanesPairs, sizeof(**planePairs), cmpDistance);
    printf("Nalezenych dvojic: %d\n", *countMin);
    for (int i = 0; i < *countMin; i++)  
    {
        if (fabs((*planePairs)[i].m_Distance - *minDistance) <= 1000 * __DBL_EPSILON__ * *minDistance)
        {
            printf ("%s - %s\n",(*planePairs)[i].m_Plane1, (*planePairs)[i].m_Plane2);
        }
    }
}

int main ( void )
{
    int planesSize = 0, planesMaxSize = 10;
    int planePairsSize = 0, planePairsMaxSize = 0; 
    double minDistance = __INT_MAX__;
    int count = 0;
    TPLANE * plane = (TPLANE*) malloc (planesMaxSize * sizeof(*plane));
    TPAIR * planePairs = NULL;
    if (!readInput( &plane, &planePairs, &planesSize, &planesMaxSize, &planePairsSize, &planePairsMaxSize, &minDistance, &count) || planesSize <= 1)
    {
        free(planePairs);
        free(plane);
        printf("Nespravny vstup.\n");
        return 1;
    }
    printOutput( &planePairs, &planePairsSize, &minDistance, &count);
    free(planePairs);
    free(plane);
    return 0;
}
