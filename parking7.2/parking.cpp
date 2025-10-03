#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 12

typedef struct TCars {
    char m_SPZ[MAX];
    int  m_Age;
    char m_IsFull;
} TCARS;

typedef struct TParkingLot {
    int m_Size;
    int m_Spots;
    int m_Iteration;
    TCARS * cars;
} TPARKING;

int readSizeParkingLot(TPARKING * parkingLot)
{
    char floor;
    printf("Velikost:\12");
    if ( scanf(" %c %d", &floor, &parkingLot->m_Spots) != 2 || parkingLot->m_Spots <= 0 || floor < 'A' || floor > 'Z')
        return 0;
   
    parkingLot->m_Size = (floor - 'A' + 1) * parkingLot->m_Spots;
    parkingLot->m_Iteration = 1;
    return 1;
}

void addCar(TPARKING * parkingLot, const char * SPZ)
{
    int min = 0;
   
    for( int i = 1; i < parkingLot->m_Size; i++){
        if (!parkingLot->cars[i].m_IsFull && parkingLot->cars[min].m_IsFull){
            min = i;
            continue;
        }
        if (parkingLot->cars[min].m_Age > parkingLot->cars[i].m_Age && parkingLot->cars[min].m_IsFull == parkingLot->cars[i].m_IsFull){
            min = i;
        }
    }
    int posNum = min % parkingLot->m_Spots + 1;
    int posAlpha = min / parkingLot->m_Spots + 'A'; 
    if(parkingLot->cars[min].m_IsFull){
        printf("Odtah vozu %s z pozice %c%d\12", parkingLot->cars[min].m_SPZ, posAlpha, posNum);
    }
    strcpy(parkingLot->cars[min].m_SPZ, SPZ);
    printf("Pozice %c%d\12", posAlpha, posNum);
    parkingLot->cars[min].m_IsFull = 1;
    parkingLot->cars[min].m_Age = parkingLot->m_Iteration++;
}

void removeCar(TPARKING * parkingLot, const char * SPZ)
{
    for (int i = 0; i < parkingLot->m_Size; i++)
    {
        if (!strcmp(SPZ, parkingLot->cars[i].m_SPZ)){
            int posNum = i % parkingLot->m_Spots + 1;
            int posAlpha = i / parkingLot->m_Spots + 'A'; 
            printf("Pozice: %c%d\12", posAlpha, posNum);
            parkingLot->cars[i].m_IsFull = 0;
            parkingLot->cars[i].m_Age = parkingLot->m_Iteration++;
            return;
        }
    }
    printf("Nenalezeno.\12");
}

int readCar(TPARKING * parkingLot)
{
    puts("Pozadavky:");
    while ( 1 )
    {
        int res;
        char mark;
        char SPZ[MAX];
        if ( (res = scanf(" %c %11s", &mark, SPZ)) != 2 || strlen(SPZ) > 10 )
            return res == EOF ? EOF : 0;
        
        switch (mark)
        {
        case '+':
            addCar(parkingLot, SPZ);
            break;
        case '-':
            removeCar(parkingLot, SPZ);
            break;
        
        default:
            return 0;
        } 
    }
    return 1;
}

int main ( void )
{
    TPARKING parkingLot = { }; 
    if (!readSizeParkingLot(&parkingLot)){
        printf("Nespravny vstup.\12");
        return 1;
    }
    
    parkingLot.cars = (TCARS*) calloc (parkingLot.m_Size, sizeof(TCARS));
    if ( !readCar(&parkingLot)){
        free(parkingLot.cars);
        printf("Nespravny vstup.\12");
        return 1;
    }

    free(parkingLot.cars);
    return 0;
}
