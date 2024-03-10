#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main(void) {
    int count = 0;
    int counted_count = 0;
    char one[MAX];
    char two[MAX];
    char counted[MAX];

    fgets(one, MAX, stdin);
    fgets(two, MAX, stdin);

    for (int i = 0; i < strlen(one); i++) {
        one[i] = tolower(one[i]);
    }
    for (int i = 0; i < strlen(two); i++) {
        two[i] = tolower(two[i]);
    }

    for (int i = 0; i < strlen(one) - 1; i++) {
        for (int j = 0; j < strlen(two) - 1; j++) {
            if (one[i] == two[j]) {
                counted[counted_count] = one[i];
                counted_count++;
                break;
            }
        }
    }
    char final_arr[MAX];

    for (int i = 0; i < strlen(counted); i++) {
        int present = 0;
        for (int j = 0; j < strlen(final_arr); j++) {
            if (counted[i] == final_arr[j]) {
                present = 1;
                break;
            }
        }

        if (present == 0 && counted[i] != ' ') {
            final_arr[count] = counted[i];
            count++;
        }
        
    }

    printf("%d\n", count);
}
