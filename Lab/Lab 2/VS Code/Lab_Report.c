#include <stdio.h>
#include <stdlib.h>
#define num_studentsALT2 14


int main(void) {
    // Question 1

    printf("    # #       # # # #    \n");
    printf("  #     #     #       #   \n");
    printf("#         #   #       #   \n");
    printf("# # # # # #   # # # #     \n");
    printf("#         #   #       #   \n");
    printf("#         #   #       #   \n");
    
    // Question 2
    
    printf("\n\n");
    
    int patient_age = 8;
    const int students1 = 12;
    float distance = 15.15;

    printf("The age of the patient is %d.\n", patient_age);
    printf("There are %d students.\n", students1);
    printf("We have %d students.\n", num_studentsALT2);
    printf("The distance is %.2f.\n", distance);
    
    
    return 0;
}