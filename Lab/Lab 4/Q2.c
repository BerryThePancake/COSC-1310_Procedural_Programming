#include <stdio.h>

int mystery(int i, int j) {
    if (i <= 0)
        return j;
    else
        return mystery(i - 1, j + 1);
}

int main() {
    int i, j; 

    printf("Enter two integers: ");
    scanf("%d\n %d", &i, &j);
    
    printf("Result: %d\n", mystery(i, j));
    
    return 0;
}