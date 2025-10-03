#include <stdio.h>
#include <stdlib.h>
#define ARRAY_EXPAND_MULTIPLIER 2

void appendChar(char ** mineArr, int* size, int* maxSize, char character)
{
	if (*size >= *maxSize)
	{
		*maxSize *= ARRAY_EXPAND_MULTIPLIER;
		*mineArr = (char*)realloc(*mineArr, sizeof(char) * (*maxSize));
	}

	(*mineArr)[*size] = character;
	(*size)++;
}

int readInput(char ** mineArr, int * size, int * maxSize, int * count)
{
    while ( 1 )
    {
        int currentChar = getchar();
        
        if (currentChar == '\n')
            break;
        if (currentChar == EOF) {
            return EOF;
        }
        if ((currentChar != '.') && (currentChar != '*')) {
            return 0;
        }             
        appendChar(mineArr, size, maxSize, currentChar);
        (*count)++;
    }
    return 1;
}
int isMine(char * mineArr, int position, int * size, char * controlled)
{
    if ((position < 0) || (position >= *size)){
        return 0;
    }
    if (controlled[position] == 0){
        if (mineArr[position] == '*'){
            controlled[position] = 1;
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
void printMineField(char * mineArray, int * size, int rows, int rowLength)
{
    char * mineField = (char*) malloc ((*size) * sizeof(*mineArray));
    
    printf("Vyplnena hraci plocha:\n");
    for (size_t i = 0; i < *size; i++){
        char * controlled = (char*) calloc ((*size), sizeof(*controlled));
        int mine = 0;
        if (mineArray[i] == '*')
        {
            mineField[i] = '*';
            continue;
        }
        for (size_t j = 0; j < 3; j++){
            int position = 0;
            if ((j == 2) && (i % rowLength != 0)){
                position = j - 3 + i;
            } 
            if ((j == 1) && ( (i + 1) % rowLength != 0)){
                position = j + i;
            }
            if (j == 0) {
                position = i;
            }
            
            mine += isMine(mineArray, (position + rowLength), size, controlled );
            mine += isMine(mineArray, (position - rowLength), size, controlled );
            mine += isMine(mineArray, (position), size, controlled );
        }
        if (mine == 0) 
            mineField[i] = '.';
        else 
            mineField[i] = mine + '0';
    }
    for (size_t i = 0; i < rows - 1; i++ ){
        for (size_t j = 0; j < rowLength; j++)
        {
            printf("%c", mineField[j+(rowLength*i)]);
        }
        printf("\n");
    }
}

int main ( void )
{
    int size = 0, maxSize = 10;
    int n = 1, prevCount;
    int iter = 0, count = 0;
    int numOfRows = 0;
    char * mineArray = (char*) malloc (maxSize * sizeof(*mineArray));
    printf("Zadejte hraci plochu:\n");
    // nacitaj plochu do 1D pola
    while( 1 ) {
        prevCount = count;
        count = 0;
        n = readInput(&mineArray, &size, &maxSize, &count);
        numOfRows++;
        if ( n == EOF)
            break;
        if ((n == 0) || ((prevCount != count) && (iter == 1))){
            printf("Nespravny vstup.\n");
            free(mineArray);
            return 1;
        }
        iter = 1;
    }
    printMineField(mineArray, &size, numOfRows, prevCount);
    if ( n != EOF ){
        free(mineArray);
        printf("Nespravny vstup.\n");
        return 1;
    }
    free(mineArray);
    return 0;
}
