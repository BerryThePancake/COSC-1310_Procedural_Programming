#include<stdio.h>
#include<stdlib.h>

int main(void){
    double num;
    printf("enter a double: ");
    scanf("%lf", &num);

    long long int converted = (long long int)num;
    printf("Converted to long long int: %lld\n", converted);
    printf("Printed on 8 positions: %8lld\n", converted);

    return 0;
}