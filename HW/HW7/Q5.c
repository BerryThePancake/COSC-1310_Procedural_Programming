/* 
Write a short program to do the following:
--allocate memory dynamically or an array of 30 integers.
--store the consecutive integers from 5 to ____(fill in the blank) in the array
--Print the array
--free the memory allocated to the array
*/


#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = malloc(30 * sizeof(int));
    for (int i = 0; i < 30; i++) {
        arr[i] = i + 5;
    }

    for (int i = 0; i < 30; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    free(arr);

    return 0;
}