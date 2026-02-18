// Create a function factorial that takes an integer n and returns n!
#include <stdio.h>

int n;

int factorial(int n)
{
    int result = 1;
    for (int i = 2; i <= n; i++)
        result *= i;
    return result;
}

int main(void)
{
    printf("Enter an integer: ");
    scanf("%d", &n);
    int result = factorial(n);
    printf("The factorial of %d is %d\n", n, result);
    return 0;
}
