#include <stdio.h>
#include <stdlib.h>

//Thanks to Hanson Lin for looking over and giving me tips

struct namevalue{
 char * name;
 char * value;
};

int q;
int i = 0;
char buffer[300], temp;
struct namevalue *s;
//s = calloc(q,sizeof(namevalue));


void readstdin(){
 while((fread(&temp,1,1,stdin))){
   buffer[i]=temp;
   i++;
 }
 buffer[i+1] = '\0';
 s = calloc(i,sizeof(s));
}

void parseinput(){
  int counter = 0, tmp = i;
  int n = 0, v = 0;
  char* name = calloc(50,1);
  char* value = calloc(50,1);//buffers to read the name and value
  while(tmp >= 0){
    if(buffer[tmp] == '|');//checks if it's the beginning of the | | and skips it
    else{
      
      while(buffer[tmp--] != ' ' || buffer[tmp] != ':') value[v++] = buffer[tmp];//while it's not : add to name buffer
      value[v] = '\0';
      s[counter].value = value;
 
      while(buffer[tmp--] != '|') name[n++] = buffer[tmp+1];//while it's not at the ending | add everything in it to value buffer
      name[0] = '=';
      name[n] = '\0';
      s[counter++].name = name;
       
      
      //prints the names
      while (n > 0){
	printf("%c",name[n--]);
      }
      
      //prints the values
      while (v > 0){
       printf("%c",value[v--]);
      } 
      
    }
    printf("\n");
  }
}

void main(){
 readstdin();
 //int i = 0;
 //while (buffer[i] != '\0'){
 //  printf("%c",buffer[i]);
 //  i++;
 //}
 parseinput();
}
