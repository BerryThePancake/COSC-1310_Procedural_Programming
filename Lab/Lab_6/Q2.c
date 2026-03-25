#include<stdio.h>
#include<stdlib.h>

int main(void){
    // forward by 3's
    for (int i = 1; i <= 36; i++){
        if (i%3==0)
            printf("%d ", i);
    }
    printf("\n");

    //reverse order
    for (int i = 36; i >= 1; i--){
        if (i%3==0)
            printf("%d ", i);
    }
    printf("\n");
}