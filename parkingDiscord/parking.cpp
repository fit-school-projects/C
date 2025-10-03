#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH_SPZ 12

typedef struct TSpot {
    char m_SPZ[MAX_LENGTH_SPZ];
    int  m_Age;
    int  m_IsFull;
} TSPOT;

typedef struct TParkingLot {
    int m_Capacity;
    int m_FreeSpots;
    int m_Floors;
    int m_CurrentAge;
    TSPOT * m_Spots;
} TPARKING;

int readParkingLotSize(TPARKING * parkingLot)
{
    printf("Velikost:\n");
    char floors, spots;
    if (scanf(" %c %c", &floors, &spots) != 2 || floors < 'A' || floors > 'Z' || spots < 'a' || spots > 'z'){
        return 0;
    }
    parkingLot->m_Capacity = (floors - 'A' + 1) * (spots - 'a' + 1);
    parkingLot->m_FreeSpots = parkingLot->m_Capacity;
    parkingLot->m_Floors = floors - 'A' + 1;
    parkingLot->m_Spots = (TSPOT*) calloc (parkingLot->m_Capacity, sizeof(TSPOT));
    return 1;
}

void printSpot(TPARKING * parkingLot, int idx)
{
    char spot = idx % (parkingLot->m_Floors + 1) + 'a';
    char floor = idx / (parkingLot->m_Floors + 1) + 'A';
    printf("Pozice: %c%c, zbyva %d\n", floor, spot, parkingLot->m_FreeSpots);
}

void addCar(TPARKING * parkingLot, const char * SPZ)
{
    if (!parkingLot->m_FreeSpots){
        printf("Plne obsazeno.\n");
        return;
    }
    int min = 0;
    for (int i = 1; i < parkingLot->m_Capacity; i++){
        if(parkingLot->m_Spots[min].m_IsFull && !parkingLot->m_Spots[i].m_IsFull)
            min = i;
        if (parkingLot->m_Spots[min].m_Age > parkingLot->m_Spots[i].m_Age && parkingLot->m_Spots[min].m_IsFull == parkingLot->m_Spots[i].m_IsFull)
            min = i;
    }
    strcpy(parkingLot->m_Spots[min].m_SPZ, SPZ);
    parkingLot->m_Spots[min].m_Age = parkingLot->m_CurrentAge++;
    parkingLot->m_Spots[min].m_IsFull = 1;
    parkingLot->m_FreeSpots--;
    // position to print
    printSpot(parkingLot, min);
}

void removeCar(TPARKING * parkingLot, const char * SPZ)
{
    for (int i = 0; i < parkingLot->m_Capacity; i++){
        if (!strcmp(parkingLot->m_Spots[i].m_SPZ, SPZ)){
            parkingLot->m_Spots[i].m_IsFull = 0;
            parkingLot->m_Spots[i].m_Age = parkingLot->m_CurrentAge++;
            parkingLot->m_FreeSpots++;
            
            printSpot(parkingLot, i);
            return;
        }
    }
    printf("Nenalezeno.\n");
}

int readCars(TPARKING * parkingLot)
{
    printf("Pozadavky:\n");
    while ( 1 )
    {
        int res;
        char SPZ[MAX_LENGTH_SPZ];
        char mark;
        if ( (res = scanf(" %c %11s", &mark, SPZ)) != 2 || strlen(SPZ) > 10)
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
    if ( !readParkingLotSize(&parkingLot)){
        printf("Nespravny vstup.\n");
        return 1;
    }
    if (!readCars(&parkingLot)){
        printf("Nespravny vstup.\n");
        free(parkingLot.m_Spots);
        return 1;
    }

    free(parkingLot.m_Spots);
    return 0;
}
