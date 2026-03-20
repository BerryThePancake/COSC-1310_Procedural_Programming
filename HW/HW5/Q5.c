#include<stdio.h>

float a, b;
int main(){
    printf("Enter two numbers: ");
    scanf("%f", &a);
    scanf("%f", &b);

    printf("The product of said numbers is: %f", a*b);
    return 0;
}