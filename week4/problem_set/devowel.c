// Tested by [Brandon Chikandiwa (z5495844) on 05/10/2023]

#include <stdio.h>

int main() {

    char devoweled[100];
    int count = 0;
    char in;
    int result_code = scanf("%c", &in);

    while (result_code == 1) {
        scanf(" %c", &in);
        devoweled[count] = in;
        count++;
    }

    for (int i = 0; i < count; i++) {
        char c = devoweled[i];
        if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') {
            printf("%c", c);
        }
    }

    return 0;
}
