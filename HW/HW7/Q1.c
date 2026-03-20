// Write a function that accepts two strings
// Count the number of characters in each
// and return a pointer to the longer string

#include <stdio.h>
#include <string.h>

char *longer_string(char *str1, char *str2) {
    if (strlen(str1) >= strlen(str2)) {
        return str1;
    } else {
        return str2;
    }
}

int main() {
    char word1[100], word2[100];

    printf("Enter first word: ");
    scanf("%99s", word1);

    printf("Enter second word: ");
    scanf("%99s", word2);

    char *result = longer_string(word1, word2);
    printf("The longer string is: %s\n", result);

    return 0;
}