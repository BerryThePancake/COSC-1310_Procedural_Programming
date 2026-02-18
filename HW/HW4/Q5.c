// Write a function average3 that takes three numbers and returns their average.
#include <stdio.h>

int average;
int a; int b; int c;
int average3(int a, int b, int c)
{
    return (a + b + c) / 3;
}

int main(void)
{
    printf("Enter three numbers: ");
    scanf("%d %d %d", &a, &b, &c);
    int result = average3(a, b, c);
    printf("The average of %d, %d, and %d is: %d\n", a, b, c, result);
    return 0;
}