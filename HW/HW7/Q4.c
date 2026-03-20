// Using an ASCII chart.
// Write a program that prints a box on-screen using the double-line characters

#include <stdio.h>

int main() {
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
    printf("%c%c            %c%c\n", 186, ' ', ' ', 186);
    printf("%c              %c\n", 186, 186);
    printf("%c              %c\n", 186, 186);
    printf("%c              %c\n", 186, 186);
    printf("%c              %c\n", 186, 186);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
    return 0;
}
