#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TparkingLot{
    char m_SPZ[10];
    int  m_Place;
    int  m_Floor;
} TPARK;

int cmpCarsBsearch(const void * a, const void * b)
{
    char * aPtr = (char*)a;
    TPARK * bPtr = (TPARK*)b;

    return strcmp(aPtr, bPtr->m_SPZ);
}

int cmpCarsQsort(const void * a, const void * b)
{
    TPARK * aPtr = (TPARK*)a;
    TPARK * bPtr = (TPARK*)b;

    return strcmp(aPtr->m_SPZ, bPtr->m_SPZ);
}

int readSizeOfTheParkinglot(TPARK ** parkingLot, int * floors, int * spots)
{
    printf("Velikost:\n");
    if ( scanf(" %d %d", floors, spots) != 2 || *floors < 1 || *spots < 1 ){
        return 0;
    }
    int maxSizeParking = *floors * *spots;
    *parkingLot = (TPARK*)malloc(maxSizeParking * sizeof(**parkingLot));
    return 1;
}

void addCar(TPARK ** parkingLot, int * sizeParkingLot, int floor, int spot, char * SPZ)
{
    for (int i = 0; i < *sizeParkingLot; i++){
        if ((*parkingLot)[i].m_Floor == floor && (*parkingLot)[i].m_Place == spot){
            if ((*parkingLot)[i].m_SPZ[0] == ' '){
                strcpy((*parkingLot)[i].m_SPZ, SPZ);
                printf("OK\n");
                return;
            }
            else {
                printf("Obsazeno %s\n", (*parkingLot)[i].m_SPZ);
                return;
            }
        }
    }
    (*parkingLot)[*sizeParkingLot].m_Floor = floor;
    (*parkingLot)[*sizeParkingLot].m_Place = spot;
    strcpy((*parkingLot)[*sizeParkingLot].m_SPZ, SPZ);
    (*sizeParkingLot)++;
    qsort(*parkingLot, *sizeParkingLot, sizeof(TPARK), cmpCarsQsort);
    printf("OK\n");
}

void removeCar(TPARK ** parkingLot, int * sizeParkingLot, char * SPZ)
{
    TPARK * foundCar = (TPARK*)bsearch(SPZ, *parkingLot, *sizeParkingLot, sizeof(TPARK), cmpCarsBsearch);
    if (foundCar){
        strcpy(foundCar->m_SPZ, " ");
        printf("OK\n");
    } else {
        printf("Nenalezeno\n");
    }
}

int readCars(TPARK ** parkingLot, int * sizeParkingLot, int floors, int spots)
{
    while ( 1 ){
        int res;
        char mark;
        if ( ( res = scanf(" %c", &mark)) != 1){
            return res == EOF ? EOF : 0;
        }   
        int floor, spot;
        char SPZ[12];
        switch (mark)
        {
            case '+':
                if ( scanf(" %d %d %11s", &floor, &spot, SPZ) != 3 || floor < 0 || spot < 0 || strlen(SPZ) > 10 || floor > floors - 1 || spot > spots - 1)
                    return 0;
                addCar(parkingLot, sizeParkingLot, floor, spot, SPZ);
                break;
            case '-':
                if ( scanf(" %11s", SPZ) != 1 || strlen(SPZ) > 10)
                    return 0;
                removeCar(parkingLot, sizeParkingLot, SPZ);
                break;
            
            default:
                return 0;
                break;
        }
    }
    return 1;
}

int main ( void )
{
    TPARK * parkingLot = NULL;
    int sizeParkingLot = 0;
    int floors, spots;
    
    if ( !readSizeOfTheParkinglot(&parkingLot, &floors, &spots)){
        printf("Nespravny vstup.\n");
        free(parkingLot);
        return 1;
    }
    if ( !readCars(&parkingLot, &sizeParkingLot, floors, spots)){
        printf("Nespravny vstup.\n");
        free(parkingLot);
        return 1;
    }

    free(parkingLot);
    return 0;
}
