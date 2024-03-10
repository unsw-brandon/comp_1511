#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TO 5000

int tribonacci(int to) {
    if (to == 0 || to == 1) {
        return 0;
    } else if (to == 2) {
        return 1;
    } else {
        int a = 0, b = 1, c = 1, result = 0;

        for (int i = 3; i <= to; ++i) {
            result = a + b + c;

            // Check for integer overflow
            if (result < 0) {
                fprintf(stderr, "Error: Integer overflow for Tribonacci(%d)\n", to);
                exit(1);
            }

            // Update values for the next iteration
            a = b;
            b = c;
            c = result;
        }

        return result;
    }
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <to>\n", argv[0]);
        return 1;
    }

    int to = atoi(argv[1]);

    if (to < 0 || to > MAX_TO) {
        fprintf(stderr, "Error: to must be between 0 and %d\n", MAX_TO);
        return 1;
    }

    clock_t start_time = clock();
    int result = tribonacci(to);
    clock_t end_time = clock();
    double elapsed_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Tribonacci(%d) = %d\n", to, result);
    printf("Elapsed time: %.6f seconds\n", elapsed_time);

    return 0;
}
