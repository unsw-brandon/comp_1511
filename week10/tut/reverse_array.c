#include <stdio.h>

int main() {
    int arr[100];
    int in;
    printf("Enter numbers forwards:\n");
    int result = scanf("%d", &in);
    int count = 0;

    while (result == 1) {
        arr[count] = in;
        result = scanf("%d", &in);
        count++;
    }

    printf("Reversed:\n");
    while (count > 0) {
        printf("%d\n", arr[count - 1]);
        count--;
    }

    return 0;
}
