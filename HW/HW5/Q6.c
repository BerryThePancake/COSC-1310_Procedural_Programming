#include<stdio.h>

int main(){
    int num = 0;
    for (int i = 0; i < 10; i++){
        int n;
        printf("Enter number %d: ", i+1);
        scanf("%d", &n);
        num += n;
    }
    printf("The sum of your numbers is: %d", num);
    return 0;
}