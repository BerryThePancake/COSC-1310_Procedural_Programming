#include <stdio.h>
int multiply(int a, int b) {
    if (a == 1) {
        return b;
    }
    return multiply(a - 1, b) + b;
}

int main() {
    int a = 4;
    int b = 5;
    int result = multiply(a, b);
    printf("The result of %d multiplied by %d is: %d\n", a, b, result);
    return 0;
}