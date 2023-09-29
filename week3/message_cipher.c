#include <stdio.h>

// This main function scans a message then enciphers/deciphers the message based
// on user input
int main(void) {
    // Have a think about how we might implement this with a `struct message`
    // once we've covered structs in the Thursday lecture!
    char letter1;
    char letter2;
    char letter3;
    char letter4;
   
    printf("Message: ");
    scanf(
        "%c %c %c %c",
        &letter1, &letter2, &letter3, &letter4
    );
}