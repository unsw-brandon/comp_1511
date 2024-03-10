// This program was written by [Brandon Chikandiwa] (z5495844)
// on [25 October 2023]

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

    int sum = 0;
    for (int i = 1; i < argc; i++) {
        sum += atoi(argv[i]);
    }
    
    printf("Sum: %d\n", sum);
    return 0;
}
