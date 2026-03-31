#include<stdio.h>
#include<math.h>


int main(void){
    double arr[50];
    for (int i = 0; i < 50; i++){
        arr[i] = sqrt(i);
        printf("%.3f ", arr[i]);
    }
}