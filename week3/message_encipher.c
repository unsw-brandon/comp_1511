#include <stdio.h>

int main() {
    char letter1, letter2, letter3, letter4;
    printf("Message: ");
    scanf("%c%c%c%c", &letter1, &letter2, &letter3, &letter4);

    int number1, number2, number3, number4;
    printf("Enter the numbers to encipher by: ");
    scanf("%d %d %d %d", &number1, &number2, &number3, &number4);

    int result1 = letter1 + number1;
    int result2 = letter2 + number2;
    int result3 = letter3 + number3;
    int result4 = letter4 + number4;

    // First Char
    if (letter1 >= 'A' && letter1 <= 'Z') {
        if (result1 > 'Z') {
            int value1 = result1 - 'Z' - 1;
            result1 -= value1;

            while (value1 > 25) {
                value1 = result1 - 'Z' - 1;
                result1 = result1 - value1;
            }

            result1 = 'A' + value1 + 1;

        } else if (result1 < 'A') {
        }
    } else if (letter1 >= 'a' && letter1 <= 'z') {

        if (result1 > 25) {
            int value1 = result1 - 'z' - 1;
            result1 -= value1;

            while (value1 > 'z') {
                value1 = result1 - 'z' - 1;
                result1 = result1 - value1;
            }

            result1 = 'a' + value1 + 1;

        } else if (result1 < 'a') {
            

            
        }
    }

    // Second Char
    if (letter2 >= 'A' && letter2 <= 'Z') {
        if (result2 > 'Z') {
            int value2 = result2 - 'Z' - 1;
            result2 -= value2;

            while (value2 > 'Z') {
                value2 = result2 - 'Z' - 1;
                result2 = result2 - value2;
            }

            result2 = 'A' + value2 + 1;

        } else if (result2 < 'A') {
        }
    } else if (letter2 >= 'a' && letter2 <= 'z') {

        if (result2 > 'z') {
            int value2 = result2 - 'z' - 1;
            result2 -= value2;

            while (value2 > 'z') {
                value2 = result2 - 'z' - 1;
                result2 = result2 - value2;
            }

            result2 = 'a' + value2 + 1;

        } else if (result2 < 'a') {
        }
    }

    // Third Char
    if (letter3 >= 'A' && letter3 <= 'Z') {
        if (result3 > 'Z') {
            int value3 = result3 - 'Z' - 1;
            result3 -= value3;

            while (value3 > 'Z') {
                value3 = result3 - 'Z' - 1;
                result3 = result3 - value3;
            }

            result3 = 'A' + value3 + 1;

        } else if (result3 < 'A') {
        }
    } else if (letter3 >= 'a' && letter3 <= 'z') {
        if (result3 > 'z') {
            int value3 = result3 - 'z' - 1;
            result3 -= value3;

            while (value3 > 'z') {
                value3 = result3 - 'z' - 1;
                result3 = result3 - value3;
            }

            result3 = 'a' + value3 + 1;

        } else if (result3 < 'a') {
        }
    }

    // Fourth Char
    if (letter4 >= 'A' && letter4 <= 'Z') {
        if (result4 > 'Z') {
            int value4 = result4 - 'Z' - 1;
            result4 -= value4;

            while (value4 > 'Z') {
                value4 = result4 - 'Z' - 1;
                result4 = result4 - value4;
            }

            result4 = 'A' + value4 + 1;

        } else if (result4 < 'A') {
        }
    } else if (letter4 >= 'a' && letter4 <= 'z') {

        if (result4 > 'z') {
            int value4 = result4 - 'z' - 1;
            result4 -= value4;

            while (value4 > 'z') {
                value4 = result4 - 'z' - 1;
                result4 = result4 - value4;
            }

            result4 = 'a' + value4 + 1;

        } else if (result4 < 'a') {
        }
    }

    printf("%c%c%c%c\n", result1, result2, result3, result4);

    return 0;
}
