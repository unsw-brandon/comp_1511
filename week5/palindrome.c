// palindrome.c
//
// Given a string, this program calculates whether it is palindromic or not and
// prints out the result.
//
// Tested by [Brandon Chikandiwa (z5495844) on 12/10/2023]

#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 1024

int is_palindrome(char my_string[MAX_STRING_LENGTH]);

//////////////// DO NOT CHANGE ANY OF THE CODE BELOW HERE //////////////////
int main(void) {
    // You don't need to understand this code to complete the exercise.

    // Scans in a string from the user.
    char my_string[MAX_STRING_LENGTH];
    fgets(my_string, MAX_STRING_LENGTH, stdin);

    // removing the newline character from the end of the string
    int length = strlen(my_string);
    if (length != 0 && my_string[length - 1] == '\n') {
        my_string[length - 1] = '\0';
    }

    // Runs your function and prints results
    if (is_palindrome(my_string)) {
        printf("%s is a palindrome!\n", my_string);
    } else {
        printf("%s is not a palindrome!\n", my_string);
    }

    return 0;
}
//////////////// DO NOT CHANGE ANY OF THE CODE ABOVE HERE //////////////////

////////////////////////////////////////////////////////////////////////////
///////////////////// ONLY WRITE CODE BELOW HERE ///////////////////////////
////////////////////////////////////////////////////////////////////////////

// Determines if the given `my_string` is a palindrome or not.
// Returns `1` if it is, otherwise `0`
int is_palindrome(char my_string[MAX_STRING_LENGTH]) {
    int len = strlen(my_string);
    int iterations = len / 2;

    int count = 0;
    while (count < iterations) {
        char letter_first = my_string[count];
        char letter_last = my_string[len - 1 - count];

        if (letter_first != letter_last) {
            return 0;
        }

        count++;
    }

    return 1;
}

////////////////////////////////////////////////////////////////////////////
///////////////////// ONLY WRITE CODE ABOVE HERE ///////////////////////////
////////////////////////////////////////////////////////////////////////////