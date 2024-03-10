// This program was written by [Brandon Chikandiwa] (z5495844)
// on [1 November 2023]

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 1024
#define MAX_STRINGS 50

struct node {
    struct node *next;
    char data[MAX_STRING_SIZE];
};

int contains(char *value, struct node *head);
struct node *strings_to_list(int len, char *strings[]);
void remove_newline(char *string);

// DO NOT CHANGE THIS MAIN FUNCTION

int main(void) {
    // Need to read in a number of ints into an array
    printf("How many strings in initial list?: ");
    int list_size = 0;
    scanf("%d", &list_size);
    getchar();
    char *initial_elems[MAX_STRINGS] = {NULL};

    int i = 0;
    while (i < list_size) {
        // Allocate string:
        char *string = malloc(sizeof(char) * MAX_STRING_SIZE);
        // scan string
        fgets(string, MAX_STRING_SIZE, stdin);
        remove_newline(string);

        initial_elems[i] = string;
        i++;
    }

    printf("Enter word to check contained: ");

    // Read in word to check that contained inside
    char value[MAX_STRING_SIZE] = {'\0'};
    fgets(value, MAX_STRING_SIZE, stdin);
    remove_newline(value);

    // create linked list from inputs
    struct node *head = NULL;
    if (list_size > 0) {
        // list has elements
        head = strings_to_list(list_size, initial_elems);
    }

    int result = contains(value, head);
    printf("%d\n", result);

    return 0;
}

// Return 1 if value occurs in linked list, 0 otherwise
int contains(char *value, struct node *head) {
    if (head == NULL) {
        return 0;
    } else if (strcmp(value, (*head).data) == 0) {
        return 1;
    } else {
        return contains(value, (*head).next);
    }
}

// DO NOT CHANGE THIS FUNCTION
// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    int i = len - 1;
    while (i >= 0) {
        struct node *n = malloc(sizeof(struct node));
        assert(n != NULL);
        n->next = head;
        strcpy(n->data, strings[i]);
        head = n;
        i -= 1;
    }
    return head;
}

// Strips newline off the end of a string.
void remove_newline(char *string) {
    int len = strlen(string);

    if (len > 0 && string[len - 1] == '\n') {
        string[len - 1] = '\0';
    }
}
