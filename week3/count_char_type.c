#include <stdio.h>
#include <string.h>

int main() {
    int vowel_count = 0;
    int consonant_count = 0;
    char sequence[100];
    printf("Enter a sequence of characters: ");
    fgets(sequence, 100, stdin);

    for (int i = 0; i < strlen(sequence); i++) {
        if (sequence[i] == 'A' || sequence[i] == 'I' || sequence[i] == 'E' || sequence[i] == 'O' || sequence[i] == 'U' ||
            sequence[i] == 'a' || sequence[i] == 'i' || sequence[i] == 'e' || sequence[i] == 'o' || sequence[i] == 'u') {
            vowel_count++;
        } else if ((sequence[i] >= 'a' && sequence[i] <= 'z') || (sequence[i] >= 'A' && sequence[i] <= 'Z')) {
            consonant_count++;
        }
    }

    printf("Number of vowels: %d\n", vowel_count);
    printf("Number of consonants: %d\n", consonant_count);

    return 0;
}
