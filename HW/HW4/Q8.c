// Create a function findMax that takes three integers (a, b, c) and returns the largest
// value (e.g., findMax(15, 27, 8) returns 27).

#include <stdio.h>
int a; int b; int c;
int findMax(int a, int b, int c)
{
    if (a >= b && a >= c)
        return a;
    else if (b >= a && b >= c)
        return b;
    else
        return c;
}

int main(void)
{
    printf("Enter three integers: ");
    scanf("%d %d %d", &a, &b, &c);
    int result = findMax(a, b, c);
    printf("The largest integer is: %d\n", result);
    return 0;
}