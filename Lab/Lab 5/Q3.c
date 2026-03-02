#include <stdio.h>
double calculate_a(int n) {
    if (n == 0) {
        return -1.0;
    }
    if (n == 1) {
        return 1.0;
    }
    if (n == 2) {
        return 0.5;
    }
    return calculate_a(n - 2) * calculate_a(n - 3);
}

int main() {
    int n = 5;
    double result = calculate_a(n);
    printf("The value of a_5 is: %.1f\n", result);
    
    return 0;
}