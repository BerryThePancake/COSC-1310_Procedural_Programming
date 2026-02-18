#include<stdio.h>

int x = 4, y = 6, z = 2;

int main()
{
    if (x==4){
        printf("x==4: True\n");
    }
    if (x != y-z){
        printf("x != y-z: True\n");
    }
    if (z == 1)
    {
        printf("z == 1: True\n");
    }
    if (y)
    {
        printf("y != 0: True\n");
    }
    else{
        printf("The rest are False\n");
    }
    return 0;
}