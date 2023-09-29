#include <stdio.h>

int main() {

  int students = 0;
  int tutors = 0;

  printf("Please enter the number of students and tutors: ");
  scanf("%d %d", &students, &tutors);
  int sum = students + tutors;
  printf("%d + %d = %d\n", students, tutors, sum);
  return 0;
}
