#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main () {
   
   /* Intializes random number generator */
   srand(time(NULL));

   /* Print 5 random numbers from 0 to 49 */
   for( int i = 0 ; i < 10000 ; i++ ) {
      printf("+ %d %d\n", rand() % 999999999, rand() % 50);
   }
   for (int i = 0; i < 5000; i++){
      printf("? %d\n", rand() % 100);
   }
   for (int i = 0; i < 5000; i++){
      printf("? %d\n", rand() % 1000);
   }
   
   return(0);
}
