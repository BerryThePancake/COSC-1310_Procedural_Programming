#include<stdio.h>

// Question 1:
int main(){

    int num1, num2;
    printf("Enter two numbers: \n");
    scanf("%d %d", &num1, &num2);
    int sum = num1 + num2;
    if (sum < 0 ){
        printf("NEGATIVE SUM\n");}
    else {
        printf("%d\n", sum);
    }
    return 0;
}


// Question 2:
int main(){
    
    int n;
    float sum = 0;
    printf("Enter a positive number: \n");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++){
        sum = sum + 1.0/i;
        printf("%f\n", sum);
    }

    return 0;
}



// Question 3:

int main(){

    

    return 0;
}