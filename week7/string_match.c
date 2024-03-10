// This program was written by [Brandon Chikandiwa] (z5495844)
// on [25 October 2023]

#include <stdio.h>
#include <string.h>

#define STR_MAX 128

int main() {
    char search_item[STR_MAX];
    char input_item[STR_MAX];
    int instances = 0;

    printf("Enter the search term: ");
    fgets(search_item, STR_MAX, stdin);

    printf("Enter the list of strings:\n");
    while (fgets(input_item, STR_MAX, stdin) != NULL) {
        if (strcmp(search_item, input_item) == 0) {
            instances++;
        }
    }
    printf("There was %d occurrence(s) of the search term in the input.\n", instances);
    return 0;
}
