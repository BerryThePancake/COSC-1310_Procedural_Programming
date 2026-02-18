// Write a function squares with two integer arguments that returns the sum of the
// squares of the arguments.

#include <stdio.h>

int a; int b;
int squares(int a, int b)
{
    return a * a + b * b;
}

int main(void)
{
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    int result = squares(a, b);
    printf("The sum of the squares of %d and %d is: %d\n", a, b, result);
    return 0;
}