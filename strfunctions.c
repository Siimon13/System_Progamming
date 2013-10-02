#include <stdio.h>
#include <string.h>

char* strup(char* s){
  int sub = 'a' - 'A';
  char* tmp = s;
  while(*s){
    if(*s >= 'a' & *s <= 'z'){
      *s = *s - sub;
    }
    *s++;
  }
  return tmp;
}

char* strfind(char* s, char* f){
  char* tmp;
  while(*s){
    if(*s == *f){
      tmp = s;
      *tmp++ = 0;
      return s;
    }
    *s++;
  }
  printf("Can't find the char \n");
  return '\0';
}


int main(){
  //char a[] = "hey";
  //printf("%d \n", 'a' - 'A');
  char f[8];
  strcpy(f, "hi there");
  printf("%s \n", strup(f));
  printf("%s \n", strfind(f, "I"));
}
