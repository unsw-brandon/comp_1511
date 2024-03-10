#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    char arr[100];
    char arr_2[100];
    int arr_2_count;

    printf("Enter text:\n");
    fgets(arr, 100, stdin);

    for (int i = 0; i < strlen(arr); i++) {
        if (arr[i] > 'a' && arr[i] < 'z') {
            arr_2[arr_2_count] = arr[i];
            arr_2_count++;
        }
    }
    char lcase[] = "abcdefghijklmnopqrstuvwxyz";

    for (int j = 0; j < strlen(arr_2); j++) {
        for (int i = 0; i < 26; i++) {
            if (arr_2[j] != lcase[i]) {
                
            } else {
                printf("%c", lcase[i]);
            }
        }
    }

    printf("\n");

    return 0;
}
