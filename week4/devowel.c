#include <stdio.h>

int main() {

    char in;
    char devoweled[100];
    int count = 0;

    while (in != '\n') {
        scanf("%c", &in);
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
