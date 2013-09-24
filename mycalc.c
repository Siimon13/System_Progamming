#include <stdio.h>
#include <string.h>

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
  printf("MAJOR KUDOS TO JING LIN!!!!!!!!!!");
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
      if(!checkInt(argv[1]) || !checkInt(argv[3])){
	printf("Invalid Value. \n");
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
      return;
    }
    printf("The answer is: %d \n", ans);
    return ans;
  }
  
}

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
int checkInt(const char* c){
     int ans = 1, n = 0, lim;
     lim = strlen(c);
     while(n < lim){
       if(c[n] == 48)
	 n++;
       else if(c[n] == 49)
	 n++;
       else if(c[n] == 49)
	  n++;
	else if(c[n] == 50)
	  n++;
	else if(c[n] == 51)
	  n++;
	else if(c[n] == 52)
	  n++;
	else if(c[n] == 53)
	  n++;
	else if(c[n] == 54)
	  n++;
	else if(c[n] == 55)
	  n++;
	else if(c[n] == 56)
	  n++;
	else if(c[n] == 57)
	  n++;
       else{
	 ans = 0;
	 break;
       }
     }
     return ans;
}


