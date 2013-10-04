#include <stdio.h>
#include <math.h>
#include <stdlib.h>


float bnrysrch(float min, float max){
  char* m1;
  char* m2;
  float mid = (min + max)/2;
  m1 = malloc(mid * sizeof(char));
  m2 = malloc((mid + 1) * sizeof(char));
  if(!m2 && m1)
    return mid;
  else{
    free(m2);
    if(m1){
      free(m1);
      return  bnrysrch(mid,max);
    }
    else{ 
      free(m1);
      return bnrysrch(min,mid);
    }
  }
  return mid;
}



char* maxmalloc(){
  char* ans;
  char* p;
  float max = 1;
  while(p){
    max *= 10;
    p = malloc(max * sizeof(char));
  }
  float min = max/10;
  printf("%f \n", max);
  free(p);
  max = bnrysrch(min , max);
  printf("%f \n", max);
  
}

int main(){
  int i = sizeof(int);
  printf("%d \n", i);
  maxmalloc();
}


