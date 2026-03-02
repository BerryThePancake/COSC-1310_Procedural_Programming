#include<stdio.h>

int calculate_a(int n);

int main(){

    int target_n = 15;

    int result = calculate_a(target_n);
    printf("a_%d = %d\n", target_n, result);
    printf("\nThe first %d terms of the sequence are:\n", target_n);
    for (int i = 0; i<=target_n; i++) {
        printf("a_%d = %d\n", i, calculate_a(i));
    }
    return 0;
}

int calculate_a(int n) {
    if (n == 0) {
        return 5;
    } else if (n > 0) {
        return 2 * calculate_a(n - 1) + 3;
    }
    return -1;
}