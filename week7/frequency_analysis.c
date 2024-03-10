// This program was written by [Brandon Chikandiwa] (z5495844)
// on [25 October 2023]

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define LETTER_COUNT 26

int main() {
    int items = 0;
    double frequencies[LETTER_COUNT] = {0};
    int freq_count[LETTER_COUNT] = {0};
    char phrase[256];

    while (fgets(phrase, 256, stdin) != NULL) {
        phrase[strlen(phrase)] = '\0';
        for (int i = 0; i < strlen(phrase); i++) {
            int position = tolower(phrase[i]);
            if (position >= 'a' && position <= 'z') {
                position -= 'a';
                items++;
                freq_count[position]++;
            }
        }
    }
    for (int i = 0; i < LETTER_COUNT; i++) {
        frequencies[i] = (double) freq_count[i] / items;
    }

    for (int i = 0; i < LETTER_COUNT; i++) {
        printf("\'%c\' %lf %d\n", 'a' + i, frequencies[i], freq_count[i]);
    }

    return 0;
}
