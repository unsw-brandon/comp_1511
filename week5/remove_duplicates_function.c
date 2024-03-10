// Tested by [Brandon Chikandiwa (z5495844) on 12/10/2023]

#include <stdio.h>

#define MAX_LENGTH 6

int remove_duplicates(int length, int source[MAX_LENGTH], int destination[MAX_LENGTH]);

int main() {
    return 0;
}

int remove_duplicates(int length, int source[MAX_LENGTH], int destination[MAX_LENGTH]) {
    int count = 0;
    int destination_size = 0;
    while (count < length) {
        int flag = 0;
        for (int i = 0; i < destination_size; i++) {
            if (source[count] == destination[i]) {
                flag = 1;
            }
        }
        if (flag == 0) {
            destination[destination_size] = source[count];
            destination_size++;
        }
        count++;
    }
    return destination_size;
}