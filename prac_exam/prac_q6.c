#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    struct node *next;
    int data;
};

int product(struct node *head1, struct node *head2);
struct node *strings_to_list(int len, char *strings[]);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(int argc, char *argv[]) {
    // create two linked lists from command line arguments
    int dash_arg = argc - 1;
    while (dash_arg > 0 && strcmp(argv[dash_arg], "-") != 0) {
        dash_arg = dash_arg - 1;
    }
    struct node *head1 = strings_to_list(dash_arg - 1, &argv[1]);
    struct node *head2 = strings_to_list(argc - dash_arg - 1, &argv[dash_arg + 1]);

    int result = product(head1, head2);
    printf("%d\n", result);

    return 0;
}

// product should return the sum of the elements in list1 multiplied by
// the corresponding element in list2
// if one list is longer than the other, the extra list elements are ignored
int product(struct node *head1, struct node *head2) {
    int count_1 = 0;
    int count_2 = 0;
    int count = 0;
    struct node *current_1 = head1;
    struct node *current_2 = head2;

    while (current_1 != NULL) {
        count_1++;
        current_1 = (*current_1).next;
    }

    while (current_2 != NULL) {
        count_2++;
        current_2 = (*current_2).next;
    }

    if (count_1 > count_2)
        count = count_2;
    else
        count = count_1;

    int total = 0;

    for (int i = 0; i < count; i++) {
        int value_1 = 0;
        int value_2 = 0;
        count_1 = 0;
        count_2 = 0;
        current_1 = head1;
        current_2 = head2;

        while (current_1 != NULL) {
            if (count_1 == i) {
                value_1 = (*current_1).data;
                break;
            }

            count_1++;
            current_1 = (*current_1).next;
        }

        while (current_2 != NULL) {
            if (count_2 == i) {
                value_2 = (*current_2).data;
                break;
            }

            count_2++;
            current_2 = (*current_2).next;
        }
        total += value_1 * value_2;
    }

    return total;
}

// DO NOT CHANGE THIS FUNCTION
// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    for (int i = len - 1; i >= 0; i = i - 1) {
        struct node *n = malloc(sizeof(struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
    }
    return head;
}
