#include <stdio.h> 
#include <stdlib.h>

int main(void){

    int array[1000]; 
    for (int a = 0; a <= 999; a++) 
        array[a] = rand ();
    int min = array[0]; 
    for (int a = 1; a <= 999; a++) 
        if(min > array[a]) 
            min = array[a];
    printf ("Min is: %d\n", min) ;
}