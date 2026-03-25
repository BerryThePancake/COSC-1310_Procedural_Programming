#include<stdio.h>
#include<stdlib.h>

int a[500];
int main(void){
    int n=36;
    do {
        if (n%3==0)
            printf("%3d", n);
        n--;
    } while (n > 0);
    printf("\n");
}