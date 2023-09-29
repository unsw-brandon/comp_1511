#include <stdio.h>

int main() {
  int response;
  printf("Year?: \n");
  scanf("%d", &response);

  if (response % 4 == 0) {
    if (response % 100 == 0) {
      if (response % 400 == 0) {
        printf("Leap year\n");
      } else {
        printf("Not leap year\n");
      }
    } else {
      printf("Leap year\n");
    }
  } else {
    printf("Not leap year\n");
  }

  return 0;
}
