#include <stdio.h>

int main() {
    int n;
    
    printf("Enter size: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("(%d, %d) ", i, j);
        }
        printf("\n");
    }

    return 0;
}
