#include <stdio.h>

int main() {
  int response;

  scanf("%d", &response);
  if (response < 0) {
    printf("Don't be so negative!\n");
  } else if (response > 0) {
    printf("You have entered a positive number.\n");
  } else {
    printf("You have entered zero.\n");
  }

  return 0;
}
