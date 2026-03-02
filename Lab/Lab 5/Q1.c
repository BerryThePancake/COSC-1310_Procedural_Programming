#include<stdio.h>

int calculate_a(int n);

int main(){

    int target_n = 5;

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
        return 1;
    } else if (n > 0) {
        return ((1+calculate_a(n - 1))*(1+calculate_a(n - 1)))/2;
    }
    return -1;
}