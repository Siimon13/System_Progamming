#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//question number 2 
float bnrysrch(float min, float max){
  char* m1;
  char* m2;
  float mid = (min + max)/2;
  m1 = malloc(mid * sizeof(char));
  m2 = malloc((mid + 1024) * sizeof(char));
  if(!m2 && m1){
    free(m2);
    free(m1);
    return mid; 
  }
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

//Shifts the char one digit
char* shift(char* ans, int lim){
  int n = 0;
  char* ptner = ans - 1;
  while(n<lim){
    ptner[n] = ans[n];
    n++;
  }
  return ptner;
}

//Puts commas into the number
char* comma(float num){
  char* ans;
  ans = malloc(sizeof(num) * sizeof(float));
  sprintf(ans, "%f",num);
  char* tmp = ans;
  while(*tmp != '.') *tmp++;
  *tmp = '\0'; 
  int i = strlen(ans) - 1;
  int counter = 1;
  while(i > 0){
    if(counter == 3){
      counter = 1;
      ans = shift(ans, i);
      ans[i] = ',';
      i--;
    }
    else{
      i--;
      counter++;
    }
  }
  return ans;
}



char* maxmalloc(){
  char* ans;
  char* p;
  float max = 1;
  while(p){
    max *= 10;
    p = malloc(max * sizeof(char));
  }
  printf("%s \n", p);
  float min = max/10;
  free(p);
  max = bnrysrch(min , max);
  ans = comma(max);
  printf("The max number of bytes allowed on malloc is: %s bytes \n", ans);
  
}

//question #3

int chkmalloc(){
  char* p;
  p = malloc(1000000);
  int i = 0;
  int sum = 0;
  while(i != 999999){
    sum |= p[i];
    i++;
  }
  if(sum != 0){
    i = 0;
  }
  return i;
}

//question 4
void matrice3(int a[][3] , int b[][3], int ans[0][3]){
  int row = 0, col = 0, row1 = 0, col1 = 0, ansrow = 0, anscol = 0;
  while(ansrow < 3){
    while(anscol < 3){
      ans[ansrow][anscol] = a[row][col++]*b[row1++][col1];
      ans[ansrow][anscol] += a[row][col++]*b[row1++][col1]; 
      ans[ansrow][anscol] +=  a[row][col]  *b[row1][col1];
      anscol++;
      col = 0;
      row1 = 0;
      col1++;
    }
    col1 = 0;
    anscol = 0;
    row++;
    ansrow++;
  }
}

//prints matrices of 3x3
void print3(int a[][3]){
  int row = 0, col = 0;
  while(row < 3){
    while(col < 3){
      printf("%2d ",a[row][col]);
      col++;
    }
    col = 0;
    printf("\n");
    row++;
  }
}

//question 5
unsigned char SetBit(unsigned char data, int bit_position, int value){
  unsigned char ans;
  if(value == 1){
    ans = pow(2, bit_position);
    ans = data | ans;
  }
  else{
    ans = pow(2, bit_position);
    data = data ^ ans;
    if(ans >= data)
      ans = data;
  }
  return ans;
}


int main(){
  //question 1
  int i = sizeof(int);
  printf("The size of an int on this OS is %d \n", i);
  //question 2
  maxmalloc();
  //question 3
  if(chkmalloc()) printf("In a malloc of size 1,000,000 all the bytes were zero'd out. \n");
  else printf("In a malloc of size 1,000,000. there was a nonzero in there. \n");
  //question 4
  int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
  printf("This is the first matrice \n");
  print3(a); 
  int b[3][3] = {{10,11,12},{13,14,15},{16,17,18}};
  printf("This is the second matrice \n");
  print3(b);
  int ans[3][3] = {{0}};
  matrice3(a,b,ans);
  printf("This is the result \n");
  print3(ans);
  //question 5
  unsigned char fred = 5;
  unsigned char result;
  result = SetBit(fred,1,1);
  printf("result: %d \n", result);  // prints 7
  result = SetBit(result,2,0);
  printf("result: %d \n", result);  // prints 3
  
}
