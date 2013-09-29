#include <stdio.h>
#include <math.h>

// 1 = true
//0 = false
int main(int argc, char* argv[]){
  if(argc == 2){
    ChkPrime(atoi(argv[1]));
  }
  else
    return ChkPrime(1000000);
}


//finds the prime number that is the limth number
int ChkPrime(int lim){
  int ans, counter = 1, n = 3;
  while(counter < lim){
    int tmp = 0;
    if(isPrime(n)){
      counter = counter + 1;
      tmp = n;
      printf("%d \n", tmp);
    }
    if(counter == lim){
      ans = n;
    }
    n = n + 2;
  }
  printf("The Answer is: %d \n", ans);
}

int isPrime(int n){
  int ans = 1;
  if(n == 2)
    return ans;
  else{
    int tmp = 3;
    int lim = pow(n, .5);
    while(tmp <= lim){
      if(n  % tmp == 0){
    ans = 0;
    break;
      }
      tmp = tmp + 2;
    }
  }
  return ans;
}

