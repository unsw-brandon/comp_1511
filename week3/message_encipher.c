// Tested by [Brandon Chikandiwa (z5495844) on 30/09/23]

#include <stdio.h>

int main() {
    char letter1, letter2, letter3, letter4;
    printf("Message: ");
    scanf("%c%c%c%c", &letter1, &letter2, &letter3, &letter4);
    
    int number1, number2, number3, number4;
    printf("Enter numbers to encipher by: ");
    scanf("%d %d %d %d", &number1, &number2, &number3, &number4);

    // Encryption for letter1
    if (letter1 >= 'A' && letter1 <= 'Z') {
        int result1 = ((letter1 - 'A' + number1) % 26 + 'A');
        if (result1 < 'A') {
            result1 += 26;
        }
        
        printf("%c", result1);
    } else if (letter1 >= 'a' && letter1 <= 'z') {
        int result1 = ((letter1 - 'a' + number1) % 26 + 'a');
        if (result1 < 'a') {
            result1 += 26;
        }
        
        printf("%c", result1);
    }

    // Encryption for letter2
    if (letter2 >= 'A' && letter2 <= 'Z') {
        int result2 = ((letter2 - 'A' + number2) % 26 + 'A');
        if (result2 < 'A') {
            result2 += 26;
        }
        printf("%c", result2);
    } else if (letter2 >= 'a' && letter2 <= 'z') {
        int result2 = ((letter2 - 'a' + number2) % 26 + 'a');
        if (result2 < 'a') {
            result2 += 26;
        }
        printf("%c", result2);
    }

    // Encryption for letter3
    if (letter3 >= 'A' && letter3 <= 'Z') {
        int result3 = ((letter3 - 'A' + number3) % 26 + 'A');
        if (result3 < 'A') {
            result3 += 26;
        }
        printf("%c", result3);
    } else if (letter3 >= 'a' && letter3 <= 'z') {
        int result3 = ((letter3 - 'a' + number3) % 26 + 'a');
        if (result3 < 'a') {
            result3 += 26;
        }
        printf("%c", result3);
    }

    // Encryption for letter4
    if (letter4 >= 'A' && letter4 <= 'Z') {
        int result4 = ((letter4 - 'A' + number4) % 26 + 'A');
        if (result4 < 'A') {
            result4 += 26;
        }
        printf("%c", result4);
    } else if (letter4 >= 'a' && letter4 <= 'z') {
        int result4 = ((letter4 - 'a' + number4) % 26 + 'a');
        if (result4 < 'a') {
            result4 += 26;
        }
        printf("%c", result4);
    }

    printf("\n");

    return 0;
}
