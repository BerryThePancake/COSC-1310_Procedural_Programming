// Create a function isLeapYear that takes an integer year and returns 1 if it is a leap year, and 0 otherwise.
#include <stdio.h>

int isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return 1;
    else
        return 0;
}

int main(void)
{
    int year;
    printf("Enter a year: ");
    scanf("%d", &year);
    if (isLeapYear(year))
        printf("%d is a leap year.\n", year);
    else
        printf("%d is not a leap year.\n", year);
    return 0;
}