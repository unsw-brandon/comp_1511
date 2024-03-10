// A program that creates its own simple scanf functions.
// Activity written by Paula

// This program was written by [Brandon Chikandiwa] (z5495844)
// on [24 October 2023]

#include <stdio.h>

void my_scanf_double(double *d) {
    double input;
    scanf("%lf", &input);
    *d = input;
}

void my_scanf_int(int *i) {
    int input;
    scanf("%d", &input);
    *i = input;
}

int main(void) {

    printf("Enter the amount of study you need to do this week (in decimal): ");
    double total_time;
    my_scanf_double(&total_time);

    printf("Enter the number of days you have free: ");
    int days;
    my_scanf_int(&days);

    double time_per_day = total_time / days;
    printf("You have on average %.2lf hour(s) each free day to do homework.\n",
           time_per_day);

    return 0;
}
