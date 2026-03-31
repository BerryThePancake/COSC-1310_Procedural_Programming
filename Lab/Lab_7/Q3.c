#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(void){
    int arr[50];
    arr[0] = 1;
    for (int i = 1; i < 50; i++){
        arr[i] = arr[i-1] + 3;
    }
    for (int i = 0; i < 50; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}