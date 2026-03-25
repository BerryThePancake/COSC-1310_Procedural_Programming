#include <stdio.h> 
#include <stdlib.h>

int main(void){
    int n = 1;
    while (n <= 200){
        if (n%4==0 && n%6==0)
            printf ("%4d", n);
        n++;
    }
    printf("\n");
}