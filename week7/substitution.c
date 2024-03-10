// This program was written by [Brandon Chikandiwa] (z5495844)
// on [25 October 2023]

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define STR_MAX 256

void change(char cipher[STR_MAX], char plain_text[STR_MAX]);

int main(int argc, char const *argv[]) {
    if (argc >= 2) {
        char cipher[STR_MAX];
        strcpy(cipher, argv[1]);

        char plain_text[STR_MAX];
        printf("Enter text:\n");

        while (fgets(plain_text, STR_MAX, stdin) != NULL) {
            change(cipher, plain_text);
        }

    } else {
        printf("No command line argument provided.\n");
    }

    return 0;
}

void change(char cipher[STR_MAX], char plain_text[STR_MAX]) {
    char cipher_text[STR_MAX];
    for (int i = 0; i < strlen(plain_text); i++) {

        char my_char = plain_text[i];
        int length = tolower(my_char) - 'a';

        if (islower(my_char) != 0) {
            cipher_text[i] = tolower(cipher[length]);
        } else if (isupper(my_char) != 0) {
            cipher_text[i] = toupper(cipher[length]);
        } else {
            cipher_text[i] = my_char;
        }
    }
    cipher_text[strlen(plain_text)] = '\0';

    printf("%s", cipher_text);
}