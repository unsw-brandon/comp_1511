// This program was written by [Brandon Chikandiwa] (z5495844)
// on [11 November 2023]

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_LEN 100

struct node {
    struct node *next;
    int data;
};

struct node *delete_highest(struct node *head);
struct node *array_to_list(int len, int array[]);
void print_list(struct node *head);
static void free_list(struct node *head);

// DO NOT CHANGE THIS MAIN FUNCTION

int main(void) {
    // scan in quantity of numbers
    printf("Total numbers in list: ");
    int list_size;
    scanf(" %d", &list_size);

    // scan numbers into array
    int n_read = 0;
    int numbers_list[MAX_LIST_LEN] = {0};
    while (n_read < list_size && scanf(" %d", &numbers_list[n_read])) {
        n_read++;
    }

    // create linked list from inputs
    struct node *head = array_to_list(n_read, numbers_list);

    struct node *new_head = delete_highest(head);
    print_list(new_head);

    free_list(new_head);

    return 0;
}

//
// Delete the node(s) in the list that contain the highest value
// The deleted node(s) are freed.
// The head of the list is returned.
//
struct node *delete_highest(struct node *head) {
    if (head == NULL) {
        return NULL;
    }

    int largest = (*head).data;
    int count = 1;
    struct node *ptr = (*head).next;

    while (ptr != NULL) {
        if ((*ptr).data > largest) {
            largest = (*ptr).data;
            count = 1;
        } else if ((*ptr).data == largest) {
            count++;
        }
        ptr = (*ptr).next;
    }

    struct node *new_head = head;
    struct node *prev = NULL;
    struct node *current = head;

    while (current != NULL) {
        struct node *next_node = (*current).next;

        if ((*current).data == largest) {
            free(current);
            if (prev == NULL) {
                new_head = next_node;
            } else {
                (*prev).next = next_node;
            }
        } else {
            prev = current;
        }

        current = next_node;
    }

    return new_head;
}

// DO NOT CHANGE THIS FUNCTION
// Free all nodes in the supplied list
static void free_list(struct node *head) {
    if (head != NULL) {
        free_list(head->next);
        free(head);
    }
}

// DO NOT CHANGE THIS FUNCTION
// create linked list from array of ints
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

// DO NOT CHANGE THIS FUNCTION
// print linked list
void print_list(struct node *head) {
    printf("[");
    struct node *n = head;
    while (n != NULL) {
        // If you're getting an error here,
        // you have returned an invalid list
        printf("%d", n->data);
        if (n->next != NULL) {
            printf(", ");
        }
        n = n->next;
    }
    printf("]\n");
}
