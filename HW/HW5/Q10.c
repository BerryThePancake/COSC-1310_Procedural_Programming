#include<stdio.h>

int power(int n){
    if (n == 0)
        return 1;
    return 3 * power(n-1);}

int main(void){
    int exp = 0;
    printf("Enter a power for 3: ");
    scanf("%d", &exp);
    printf("3 to the power of %d is: %d", exp, power(exp));
    return 0;}