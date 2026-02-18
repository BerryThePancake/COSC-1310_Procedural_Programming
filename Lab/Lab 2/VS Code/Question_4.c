#include <stdio.h>

int main() {
    short s = 32767;
    printf("The size of s is %d\n", sizeof(s));
    printf("Size of short: %d\n ", sizeof(short));
    printf("Size of signed short integer: %d\n", sizeof(signed short int));



    unsigned short t = 32768;
    printf("The size of t is %d\n", sizeof(t));
    printf("Size of unsigned short: %d\n ", sizeof(unsigned short));
    printf("Size of unsigned short integer: %d\n", sizeof(unsigned short int));
    
    return 0;
}