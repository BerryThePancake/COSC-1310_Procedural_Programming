#include <stdio.h>

#define MAX_SIZE 100

int main(void) 
{
    int numbers[MAX_SIZE];
    int input;
    int count = 0;

    printf("Enter integers (enter 0 to stop):\n");
    while (count < MAX_SIZE) {
        scanf("%d", &input);
        if (input == 0) 
            break; 
        numbers[count] = input;
        count++;}
    if (count == 0){
        printf("No numbers were entered.\n");
        return 0;}
    int min = numbers[0];
    int max = numbers[0];
    for (int i = 1; i < count; i++){
        if (numbers[i] < min)
            min = numbers[i];
        if (numbers[i] > max) 
            max = numbers[i];}
    printf("Smallest value: %d\n", min);
    printf("Largest value: %d\n", max);

    return 0;
}