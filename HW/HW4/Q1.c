// Write a function max2 that takes two intergers as input and returns the larger one.
#include <stdio.h>

int a;
int b;

int max2(int a, int b)
{
    if (a>b)
        return a;
    else
        return b;
}

int main(void)
{
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    int result = max2(a, b);
    printf("The larger integer is: %d\n", result);
    return 0;
}
