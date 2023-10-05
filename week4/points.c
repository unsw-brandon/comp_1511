//
// Written INSERT-DATE-HERE
// By INSERT-AUTHOR-HERE
//
// INSERT-DESCRIPTION-HERE
//

#include <stdio.h>

#define MAX_POINTS 10

struct point {
    // TODO: fill this in so that the struct can hold an x and y position
    //
    // i.e. This struct should contain:
    //      the x-coordinate and y-coordinate (doubles).

    double x;
    double y;
};

// Prints a point out.
void print_point(int point_no, double x, double y);

int main(void) {
    // TODO: Declare an array of points of size MAX_POINTS
    int count = 0;
    int point_count;
    struct point points_array[MAX_POINTS];
    printf("How many points in the shape? ");
    // TODO: scan in number of points in the shape
    scanf("%d", &point_count);
    printf("Enter points:\n");
    // TODO: scan in the details of each point into the array
    while (count != point_count) {
        double x, y;
        scanf("%lf %lf", &x, &y);
        struct point scanned_point = {x, y};
        points_array[count] = scanned_point;
        count++;
    }

    printf("\nShape Points:\n");
    // TODO: print all the points
    for (int i = 0; i < count; i++) {
        print_point(i + 1, points_array[i].x, points_array[i].y);
    }

    return 0;
}

//  Prints a single point in the correct format.
//
// Parameters:
// - `point_no` -- The point number
// - `x`        -- The x-coordinate of the point
// - `y`        -- The y-coordinate of the point
//
// Returns: nothing.
void print_point(int point_no, double x, double y) {
    printf("%2d: x = %.3lf, y = %.3lf\n", point_no, x, y);
}