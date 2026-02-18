// Write a function isEven that takes an integer and returns 1 for even and 0 for odd
#include <stdio.h>

int num;
int isEven(int number)
{
    if (number % 2 == 0)
        return 1;
    else
        return 0;
}

int main(void)
{
    printf("Enter an integer: ");
    scanf("%d", &num);
    if (isEven(num))
        printf("%d is even.\n", num);
    else
        printf("%d is odd.\n", num);
    return 0;
}