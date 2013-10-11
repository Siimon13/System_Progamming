#include <stdio.h>

int main(int argv, char* arg[]){
  FILE *fp;
  char lines[200];
  if(fp = fopen(arg[1], "r")){
    if(fgets(lines,199,fp))
      printf("%s", lines);
  }

}
