#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct namevalue{
  char* name;
  char* value;
};


char* buffer;
int i = 0;
struct namevalue* s;

void ReadStdin(){
  //short int i=0;
  char chr[1];
  buffer=malloc(1);
  while (1) {
    fread(chr,1,1,stdin);
    if (chr[0]=='\n') {
      fread(chr,1,1,stdin);
      if(chr[0] != '|'){
	buffer[i]='\0';
	break;
      }
      else{
	buffer[i++] = '\n';
      }
    }
    buffer[i++]=chr[0];
    buffer=realloc(buffer,i+2);
  }
  s = calloc(i,sizeof(s));
}




void ParseInput(){
  int counter = 0, tmp = i,n,v;
  char* name = calloc(30,1);
  char* value = calloc(30,1);//buffers to read the name and value
  while(tmp >= 0){
    if(buffer[tmp--] == '|');//checks if it's the beginning of the | | and skips it
    else{
      while(buffer[tmp--] != ':')name[n++] = buffer[tmp];//while it's not : add to name buffer
      name[n] = '=';//Add the equal sign
      name[n] = '\0';
      s[counter].name = name;
      while(buffer[tmp--] != '|')value[v++] = buffer[tmp];//while it's not at the ending | add everything in it to value buffer
      value[v] = '\n';//goes to next line
      value[v] = '\0';
      s[counter++].value = value;
      v = 0;
      n = 0;
    }
  }
  printf("Stuff");
}

void main(int argc, char* argv[]){
  ReadStdin();
  ParseInput();
  // fwrite(p, sizeof(stdin), 300, stdout);
  //fclose(p);
}
