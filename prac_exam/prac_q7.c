#include <stdio.h>
#include <stdlib.h>

#define ARR_MAX 10000

int main(void) {
    int arr[ARR_MAX];
    int arr_out[ARR_MAX];

    int value;
    int count = 0;
    int count_out = 0;
    scanf("%d", &value);
    while (value != 0) {
        arr[count] = value;
        scanf("%d", &value);
        count++;
    }

    for (int i = 0; i < count; i += 2) {
        arr_out[count_out] = arr[i];
        count_out++;
    }

    for (int i = 1; i < count; i += 2) {
        arr_out[count_out] = arr[i];
        count_out++;
    }
    
    for (int i = 0; i < count_out; i++) {
        printf("%d ", arr_out[i]);
    }

    printf("\n");
}
