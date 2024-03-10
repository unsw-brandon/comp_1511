// stellar_information.c
//
// This program simulates a star system in space
//
// This program was written by [Brandon Chikandiwa] (z5495844)
// on [25 October 2023]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONVERSION_CONSTANT 9.461e12
#define LIGHT_SPEED 299792.458
#define STR_MAX 50

struct star {
    char name[STR_MAX];
    double distance;
    char spectral_type;
};

// TODO: TASK 1

void print_star_information(struct star *star);
void input_star_information(struct star *star);
double time_travel(struct star *star);

int main() {
    // TODO: TASK 2
    struct star star_ptr;

    input_star_information(&star_ptr);
    print_star_information(&star_ptr);

    return 0;
}

// Takes in the stars information
void input_star_information(struct star *star) {
    // TODO: TASK 3

    printf("Enter the star's name: ");
    char name[STR_MAX];
    fgets(name, STR_MAX, stdin);
    memcpy((*star).name, name, STR_MAX);

    printf("Enter the star's distance from Earth (in light-years): ");
    double distance;
    scanf("%lf", &distance);
    (*star).distance = distance;

    printf("Enter the star's spectral type: ");
    char spectral_type;
    scanf(" %c", &spectral_type);
    (*star).spectral_type = spectral_type;
}

// Estimate travel time from Earth to the star based on star's distance
double time_travel(struct star *star) {
    // TODO: TASK 4

    return ((*star).distance * CONVERSION_CONSTANT) / LIGHT_SPEED;
}

// Prints the stars information
void print_star_information(struct star *star) {
    // TODO: TASK 5

    printf("\n");
    printf("Star's Information: \n");
    printf("Name: ");
    fputs((*star).name, stdout);
    printf("Distance: %lf light-years\n", (*star).distance);
    printf("Spectral Type: %c\n", (*star).spectral_type);
    printf("Estimated travel time from Earth: %.*f seconds\n", 2, time_travel(star));
}
