
#define _USE_MATH_DEFINES
#include<stdio.h>
#include<math.h>


const long double pi = M_PI;
float Volume(float r){
    float volume = (4.0/3.0) * pi * (r*r*r);
    return volume;
}

int main(){
    float radius;
    printf("Enter the radius of the sphere: ");
    scanf("%f", &radius);
    printf("The volume of the sphere is: %.2f\n", Volume(radius));
}