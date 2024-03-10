// This program was written by [Brandon Chikandiwa] (z5495844)
// on [11 November 2023]

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *next;
    int data;
};

int get_middle(struct node *head);
struct node *array_to_list(int len, int array[]);

// DO NOT CHANGE THIS MAIN FUNCTION
#define MAX_INIT_LIST_LEN 100
int main(void) {
    // Need to read in a number of ints into an array
    printf("How many numbers in initial list?: ");
    int list_size = 0;
    scanf("%d", &list_size);
    int initial_elems[MAX_INIT_LIST_LEN] = {0};
    int n_read = 0;
    while (n_read < list_size && scanf("%d", &initial_elems[n_read])) {
        n_read++;
    }

    // create linked list from first set of inputs
    struct node *head = NULL;
    if (n_read > 0) {
        // list has elements
        head = array_to_list(n_read, initial_elems);
    }

    int result = get_middle(head);
    printf("%d\n", result);

    return 0;
}

// Return middle element of a linked list
// if list contains [6,7,8,9,10]  8 is returned
// if a list has even number of elements, first of middle two elements returned
// if list contains [1,2,3,4] 2 is returned
// list can not be empty
int get_middle(struct node *head) {
    struct node *step_1 = head;
    struct node *step_2 = head;

    if ((*step_2).next == NULL) {
        return (*head).data;
    }

    while (step_2 != NULL && (*(*step_2).next).next != NULL) {
        step_2 = (*(*step_2).next).next;
        step_1 = (*step_1).next;
    }

    return (*step_1).data;
}

// DO NOT CHANGE THIS FUNCTION

// create linked list from array of strings
struct node *array_to_list(int len, int array[]) {
    struct node *head = NULL;
    int i = len - 1;
    while (i >= 0) {
        struct node *n = malloc(sizeof(struct node));
        assert(n != NULL);
        n->next = head;
        n->data = array[i];
        head = n;
        i -= 1;
    }
    return head;
}
