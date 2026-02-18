// Write code that will take the area of a cone
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>


int main()
{
    float area; float radius; float height;
    printf("Enter the radius of the cone: ");
    scanf("%f", &radius);
    printf("Enter the height of the cone: ");
    scanf("%f", &height);

    area = M_PI * radius * (radius + sqrt(height*height + radius*radius));
    printf("The area of the cone is: %.2f", area);

    return 0;
}