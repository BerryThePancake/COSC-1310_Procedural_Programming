#include<stdio.h>
int main()
{
    int count = 1;
    for (int i = 1; i <= 100; i++){
        if (i%3 == 0){
            count = (count+3);
            printf("Count: %d\n", count);
        }
    }
    return 0;
}