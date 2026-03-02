#include <stdio.h>
double calculate_a(int n) {
    if (n == 0) {
        return 1.0;
    }
    else {
        double prev = calculate_a(n - 1);
        return ((prev + 1.0) * (prev + 1.0)) / 2.0;
    }
}

int main() {
    int n = 3;
    double result = calculate_a(n);
    printf("The value of a_3 is: %.3f\n", result);
    return 0;
}