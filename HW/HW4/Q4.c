// Create a function fahrenheitToCelsius that takes a double Fahrenheit temperature and returns the Celsius value: C = (F - 32) * 5/9.
#include <stdio.h>

double fahrenheit;
double celsius;
double fahrenheitToCelsius(double fahrenheit)
{
    return (fahrenheit - 32) * 5.0 / 9.0;
}

int main(void)
{
    printf("Enter a temperature in Fahrenheit: ");
    scanf("%lf", &fahrenheit);
    double celsius = fahrenheitToCelsius(fahrenheit);
    printf("%.2lf degrees Fahrenheit is %.2lf degrees Celsius.\n", fahrenheit, celsius);
    return 0;
}