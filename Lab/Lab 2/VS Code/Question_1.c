#include <stdio.h>
#include <math.h>


int main() {

char line1[] = "# # # # #   ";
char line2[] = "#         # ";
char line3[] = "#       #   ";
char line4[] = "# # # #     ";
char line5[] = "#       #   ";
char line6[] = "#         # ";

for (int i = 0; i < 6; i++) {
    if (i == 0) {
        printf("%s\n", line1);
    } else if (i == 1) {
        printf("%s\n", line2);
    } else if (i == 2) {
        printf("%s\n", line3);
    } else if (i == 3) {
        printf("%s\n", line4);
    } else if (i == 4) {
        printf("%s\n", line5);
    } else {
        printf("%s\n", line6);
    }
}

return 0;
}



