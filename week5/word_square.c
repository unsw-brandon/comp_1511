// Tested by [Brandon Chikandiwa (z5495844) on 05/10/2023]

#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

int main() {
    char word[MAX_SIZE];
    printf("Input Word: ");
    fgets(word, MAX_SIZE, stdin);
    int len = strlen(word);
    printf("\n");

    printf("Word square is: \n");
    for (int i = 0; i < len - 1; i++) {
        fputs(word, stdout);
    }

    return 0;
}