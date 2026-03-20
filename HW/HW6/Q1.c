// Write a function named 'addarrays()' taht sccpets two arrays that are the same size
// The function should add the two arrays together and return the result in a third array

#include <stdio.h>
#define SIZE 5

void addarrays(int arr1[], int arr2[], int result[], int size) {
    for (int i = 0; i < size; i++) {
        result[i] = arr1[i] + arr2[i];
    }
}


// had to make something in the main function otherwise C
// wouldve thrown a fit :(
int main(){
    int arr1[SIZE] = {1, 2, 3, 4, 5};
    int arr2[SIZE] = {1, 2, 3, 4, 5};
    int result[SIZE];

    addarrays(arr1, arr2, result, SIZE);
    printf("Result of adding the two arrays:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", result[i]);}

    return 0;
}