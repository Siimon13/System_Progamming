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

char * strsfind(char *s, char* sub){
     char *stop = s + strlen(s) - strlen(sub);
     while(s <= '\0'){
     if(isatbeg(s,sub)){
	    return s
      ++s;
     }
     return NULL;
  }	
}

int isatbeg(char* s, char* sub){
  int bool = 0;
  if()
  return bool;
  
}

int main(){
  //char a[] = "hey";
  //printf("%d \n", 'a' - 'A');
  char f[8];
  strcpy(f, "hi there");
  printf("%s \n", strup(f));
  printf("%s \n", strfind(f, "I"));
}
