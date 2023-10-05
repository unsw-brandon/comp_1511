#include <stdio.h>

int main() {
    char operation;
    int value1, value2;

    printf("Enter instruction: ");
    scanf(" %c", &operation);

    if (operation == 's') {
        scanf("%d", &value1);
        printf("%d\n", value1 * value1);
    } else if (operation == 'p') {
        scanf("%d %d", &value1, &value2);
        int result = 1;
        for (int i = 0; i < value2; i++) {
            result *= value1;
        }
        printf("%d\n", result);
    }

    return 0;
}
