// Q1 for lab


#include<stdio.h>
#include<math.h>
#include<time.h>

int main(){

    /* double D = 1000;
    int init_Dep = D;
    float r = 0.05;
    int year_index = 1;

    while (D < (2*init_Dep)){

        D = (1 + r) * D;
        // printf("Balance after %d years: %.2lf\n", year_index, D);
        year_index++;
    }
    printf("Balance after %d years: %.2lf\n", year_index, D);
    */


    /* Q2 practice
    for (int i = 1; i<=20; i++){
        if (i%2 ==0)
            printf("%d ", i);
    }*/


    /* array question 4
    int i = 0; 
    int A[20];
    for (int i = 0; i<20; i++){
        A[i] = (i+1)*5;
        printf("A[%d] = %d\n", i, A[i]);
        sum += A[i];
    }*/

    srand(time(NULL));
    int A[500];

    for (int i = 0; i < 500; i++){
        A[i] = rand();
    }

    int largest_int = 0;
    int loc = 0;

    for (int i = 0; i < 500; i++){
        if (A[i] > largest_int){
            largest_int = A[i];
            loc = i;
        }

    }


    return 0;
}