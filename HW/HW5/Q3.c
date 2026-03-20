#include <stdio.h>

int main() {
    int number = 1;
    do {
        printf("%d\n", number);
        number += 3;
    } while (number <= 100);
    return 0;
}