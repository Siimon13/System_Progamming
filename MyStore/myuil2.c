#include <stdio.h>
#include <string.h>

struct NameValue{
  char* name;
  char* value;
};

ReadStdin(){
  int i;
  char* c;
  fread(c, sizeof(stdin), 300, stdin);
  int counter;
  while(c[i] != EOF){
    if(c[i] == '|'){
      counter++;
    }
  }
}

ParseInput(){
  
}

int main(int argc, char* argv[]){
  ReadStdin();
  // fwrite(p, sizeof(stdin), 300, stdout);
  //fclose(p);
}
