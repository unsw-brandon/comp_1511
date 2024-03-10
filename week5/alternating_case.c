// Tested by [Brandon Chikandiwa (z5495844) on 05/10/2023]

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 1024

//////////////// DO NOT CHANGE ANY OF THE CODE BELOW HERE //////////////////
void make_alternating(char string[MAX_STRING_LENGTH]);

int main(void) {
    // You don't need to understand this code to complete the exercise.

    // Scans in a string from the user.
    char buffer[MAX_STRING_LENGTH];
    fgets(buffer, MAX_STRING_LENGTH, stdin);

    // Runs your function
    make_alternating(buffer);

    // Prints resulting string.
    printf("%s", buffer);

    return 0;
}
//////////////// DO NOT CHANGE ANY OF THE CODE ABOVE HERE //////////////////

////////////////////////////////////////////////////////////////////////////
///////////////////// ONLY WRITE CODE BELOW HERE ///////////////////////////
////////////////////////////////////////////////////////////////////////////

// Modifies `string` so that the first letter is converted to lowercase,
// and the case of each following letter alternates.
// i.e. in the resulting string:
//      the first letter is lowercase,
//      second letter is uppercase,
//      third letter is lower case,
//      etc.
//
// e.g.: "Hello" -> "hElLo"
void make_alternating(char string[MAX_STRING_LENGTH]) {
    int len = strlen(string);
    int count = 0;
    int word_count = 0;
    int prev = 0;
    while (count < len) {
        if (word_count % 2 != 0) {
            if (prev == 0) {
                string[count] = toupper(string[count]);
            } else {
                string[count] = tolower(string[count]);
            }
        } else {
            if (prev == 0) {
                string[count] = tolower(string[count]);
            } else {
                string[count] = toupper(string[count]);
            }
        }

        if (string[count] == ' ') {
            if (islower(string[count - 1])) {
                prev = 1;
            } else {
                prev = 0;
            }

            word_count = 0;
        } else {
            word_count++;
        }

        count++;
    }
}

////////////////////////////////////////////////////////////////////////////
///////////////////// ONLY WRITE CODE ABOVE HERE ///////////////////////////
////////////////////////////////////////////////////////////////////////////