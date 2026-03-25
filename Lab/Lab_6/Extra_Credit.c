#include <stdio.h>

float B(int n) {
  if (n == 0){
    return 1000.0;} 
    return B(n - 1) * 1.05;
}

int main(void) {
  int n = 15;
  float final_money = B(n);
  printf("The balance after %d years is: $%.2f\n", n, final_money);
  
}