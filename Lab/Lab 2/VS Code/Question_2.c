#include <stdio.h>
#include <stdlib.h>
#define num 42

int main() {
    printf("The constant integer 'num' is %d\n", num);
    
    const int const_x = 42;
    printf("The constant integer 'const_x' is %d\n", const_x);

    int x = 42;
    printf("The variable x is %d\n", x);    
    
    return 0;
}