#include <stdio.h>

#define MIN_GRADE 0
#define MAX_GRADE 100
#define LINE "----------------------------------------"

/* Updates the official grade in place (no copies are made). */
void applyExtraCredit(int *grade, int extraCredit) {
  *grade = *grade + extraCredit;
}

int main(void) {
  int grade;       /* the ONE official grade */
  int extraCredit; /* extra credit points to award */

  /* Input: original grade (re-ask until it is valid) */
  do {
    printf("Enter the student's original grade (%d-%d): ", MIN_GRADE,
           MAX_GRADE);
    scanf("%d", &grade);
    if (grade < MIN_GRADE || grade > MAX_GRADE) {
      printf("Invalid grade. Please try again.\n");
    }
  } while (grade < MIN_GRADE || grade > MAX_GRADE);

  /* Input: extra credit points (re-ask until it is not negative) */
  do {
    printf("Enter the extra credit points to award: ");
    scanf("%d", &extraCredit);
    if (extraCredit < 0) {
      printf("Extra credit cannot be negative. Please try again.\n");
    }
  } while (extraCredit < 0);

  /* Report: header and the grade BEFORE the update */
  printf("\n");
  printf("%s\n", LINE);
  printf("Sunshine Elementary School\n");
  printf("Grade Adjustment Report\n");
  printf("%s\n", LINE);
  printf("Original Grade : %d\n", grade);
  printf("Extra Credit : %d\n", extraCredit);

  /* Update the official grade in place */
  applyExtraCredit(&grade, extraCredit);

  /* Report: the grade AFTER the update */
  printf("Corrected Grade: %d\n", grade);

  return 0;
}
