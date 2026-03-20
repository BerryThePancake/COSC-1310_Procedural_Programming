// Create an array of 10 integers and initialize it with elements of your choice.
// (OK to use rand if you want)
// Write a function that prints the array in reverse order.
// The function does not return anything
// Test the function in the main program

#include <stdio.h>
#define SIZE 10

void printReverse(int arr[], int size) {
    for (int i = size - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
}

int main(){
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("Array in order:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nArray in reverse order:\n");
    printReverse(arr, SIZE);

    return 0;
}