#include <stdio.h>

int rec(unsigned int x, unsigned int y){
  if(!x && !y) return 0;
    return rec(y>>1,x>>1)+(x&1)+(y&1);
}
 
int main(void){
    printf("%d %d", rec(26,24),rec(26,28));
    return 0;
}
