// Write a function square that takes one integer argument and returns its square (e.g., square(7) returns 49).
#include <stdio.h>

int square(int number)
{
    return number * number;
}

int main(void)
{
    int number;
    printf("Enter an integer: ");
    scanf("%d", &number);
    int result = square(number);
    printf("The square of %d is %d\n", number, result);
    return 0;
}