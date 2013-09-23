#include <stdio.h>
#include <string.h>
//Does not work when you input *, Use \* for multiplication
//Does not return an error if an char
//Need to add /0 exception and return an error if characters are in my input.


//Echo
void echo(int argc, char* argv[]){
     int i;
     for(i = 0; i < argc; ++i){
     	   printf("argv[%d]: %s \n", i , argv[i]);
     }
}

//strcpy function
char* mystrcpy(char* d1,const char* c1){
  int cnter = 0;
  while(c1[cnter] != '\0'){
    d1[cnter] = c1[cnter];
    cnter++;
  }
  d1[cnter] = '\0';
  return d1;
}

//strcat function
char* mystrcat(char* d1,const char* c1){
  int i = strlen(d1);
  while (c1[i] != '\0'){
    d1[i] = c1[i];
    i++;
  }
  d1[i] = '\0';
  return d1;
}

/*
//Calcualtor, use atoi
int myCalc(int argc, char* argv[]){
  int firstNum, sign, scdNum;
  int chkfirst, chkscnd;
  chkfirst = strlen(argv[0]);
  chkscnd = strlen(argv[2]);
  
}
*/

int main(int argc, char* argv[]){
  if(argc < 4){
    printf("Add more STUFF! \n");
    return;
  }
  else if(argc > 4){
    printf("TOO MUCH STUFF! \n");
    return;
  }
  else{
    int firstNum, ans, scndNum;
    int chkfirst, chkscnd, c1, c2;
    chkfirst = strlen(argv[1]);
    chkscnd = strlen(argv[3]);
    firstNum = atoi(argv[1]);
    scndNum = atoi(argv[3]);
    c1 = countDig(firstNum);
    c2=  countDig(scndNum);
    if(firstNum == 0 || scndNum == 0){
     if(!checkInt(argv[3]) || !checkInt(argv[1])){
          printf("Illegal Value. \n");
          return;
     }
     else if(scndNum == 0){
          printf("DIVIDE BY ZERO?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!");
          return;
     }
    }
    if(c1 != chkfirst || c2 != chkscnd){
      printf("Illegal Value. \n");
      return;
    }
    if(strcmp(argv[2], "+") == 0){
      ans = firstNum + scndNum;
    }
    else if(strcmp(argv[2], "-") == 0){
      ans = firstNum - scndNum;
    }
    else if(strcmp(argv[2], "*") == 0){
      ans = firstNum * scndNum;
    }
    else if(strcmp(argv[2], "/") == 0){
      ans = firstNum / scndNum;
    }
    else{
      printf("Input a Valid Operation \n");
    }
    printf("The answer is: %d \n", ans);
    return ans;
  }
  
}

//Counts the number of Digits in an integer
int countDig(int n){
  int ans = 1;
  if(n < 0)
    ans = 2;
  while(n > 10){
    n = n/10;
    ans++;
  }
  return ans;
}

//Returns 0 if it is not an integer, 1 if it is
int checkInt(char* c){
     int ans = 1, n = 0, lim;
     lim = strlen(c);
     while(n < lim){
          if(strcmp(c[n], "1") == 0)
               n++;
          else if(strcmp(c[n], "2") == 0)
               n++;
          else if(strcmp(c[n], "3") == 0)
               n++;
          else if(strcmp(c[n], "4") == 0)
               n++;
          else if(strcmp(c[n], "5") == 0)
               n++;
          else if(strcmp(c[n], "6") == 0)
               n++;
          else if(strcmp(c[n], "7") == 0)
               n++;
          else if(strcmp(c[n], "8") == 0)
               n++;
          else if(strcmp(c[n], "9") == 0)
               n++;
          else if(strcmp(c[n], "0") == 0)
               n++;
          else{
               ans = 0;
               break;
          }
     }
}
