#include <stdio.h>

int main() {
    int response;
    printf("Enter number: ");
    scanf("%d", &response);

    if (response > 0) {
        for (int i = 0; i <= response; i++) {
            printf("%d\n", i);
        }
    } else {
        for (int i = 0; i >= response; i--) {
            printf("%d\n", i);
        }
    }

    return 0;
}
