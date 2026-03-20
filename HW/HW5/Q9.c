#include<stdio.h>

int x[10];


int main(void){
    for (int i = 0; i < 10; i++) {
        x[i] = i;
        printf("The value of x[%d] is: %d\n", i, x[i]);
    }
    return 0;
}
