#include  <stdio.h>

int age;
int main(void)
{
    printf("Enter your age: ");
    scanf("%d", &age);
    if (age >= 65)
        printf("Have you bought a coffin yet?\n");
    else if (age <= 21)
        printf("Youre just a kid, go play outside.\n");
    else
        printf("You are old enough to know how to code.\n");
    return 0;
}