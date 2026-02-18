#include <stdio.h>

int main() {
    short s = -32767;
    printf("The variable s is %hd\n", --s);
    
    
    short s1 = -32768;
    printf("The variable s1 is %hd\n", --s1);
    
    return 0;
}