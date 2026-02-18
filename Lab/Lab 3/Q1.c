#include<stdio.h>

int main()
{
    float x;
    scanf("Enter a value: %f", &x);
    if (x > 0){
        printf("X is positive!");}
    else if (x < 0){
        printf("X is negative!");}
    else{
        printf("X is zero!");}
    return 0;
    
}