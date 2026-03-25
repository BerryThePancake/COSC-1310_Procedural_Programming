#include <stdio.h>

int main(void) {
    float Balance = 1000.0f;
    float rate = 0.05f;

    int n = 1;
    while (Balance <= 3000.0f) {
        Balance *= (1.0f + rate);
        n++;
    }
    
    printf("Year %i balance $%.2f\n", n - 1, Balance);
    
    return 0;
}