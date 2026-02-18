// Write the declaration (prototype) for a function squares that returns the sum of the
// squares of its two double arguments.
#include <stdio.h>

// 1. Function Declaration (The Prototype)
double squares(double a, double b){
    return (a * a) + (b * b);
}

int main() {
    double x, y;
    printf("Enter two numbers: ");
    scanf("%lf %lf", &x, &y);
    printf("The sum of squares is: %f\n", squares(x, y));
    return 0;
}
