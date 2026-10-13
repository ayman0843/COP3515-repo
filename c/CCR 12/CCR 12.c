/*
 * CCR-012 - Insight Market Research Group
 * Survey Summary Program
 *
 * Asks how many survey scores will be entered, reserves exactly that much
 * storage with malloc(), reads the scores, reports the highest, lowest and
 * average score, then frees the memory before the program ends.
 */

#include <stdio.h>
#include <stdlib.h>

#define LINE_WIDTH 40

/* Function prototypes */
int readInteger(const char *prompt, int *value);
int findHighest(const int *scores, int count);
int findLowest(const int *scores, int count);
double calculateAverage(const int *scores, int count);
void printLine(void);
void printReport(const int *scores, int count);

int main(void) {
  int count = 0;
  int *scores = NULL;
  int i;

  /* Ask how many scores will be entered (must be at least 1) */
  do {
    if (!readInteger("Number of Survey Scores: ", &count)) {
      printf("Error: input ended before the number of scores was entered.\n");
      return 1;
    }
    if (count < 1) {
      printf("Please enter a whole number of 1 or more.\n");
    }
  } while (count < 1);

  /* Reserve storage for exactly 'count' scores */
  scores = (int *)malloc(count * sizeof(int));
  if (scores == NULL) {
    printf("Error: not enough memory for %d survey scores.\n", count);
    return 1;
  }

  /* Read every score */
  for (i = 0; i < count; i++) {
    char prompt[32];
    sprintf(prompt, "Score %d: ", i + 1);

    if (!readInteger(prompt, &scores[i])) {
      printf("Error: input ended before all scores were entered.\n");
      free(scores);
      scores = NULL;
      return 1;
    }
  }

  /* Display the summary report */
  printReport(scores, count);

  /* Release the memory */
  free(scores);
  scores = NULL;

  printf("Memory released successfully.\n");
  printf("Program completed.\n");

  return 0;
}

/*
 * Prompts for a whole number and keeps asking until one is entered.
 * Returns 1 on success, 0 if the input ends (end-of-file).
 */
int readInteger(const char *prompt, int *value) {
  int result;
  int ch;

  while (1) {
    printf("%s", prompt);
    result = scanf("%d", value);

    if (result == EOF) {
      return 0;
    }

    /* Throw away anything left on the line (including bad input) */
    while ((ch = getchar()) != '\n' && ch != EOF) {
      /* discard */
    }

    if (result == 1) {
      return 1;
    }

    printf("Invalid entry. Please enter a whole number.\n");
  }
}

/* Returns the largest score in the array */
int findHighest(const int *scores, int count) {
  int highest = scores[0];
  int i;

  for (i = 1; i < count; i++) {
    if (scores[i] > highest) {
      highest = scores[i];
    }
  }
  return highest;
}

/* Returns the smallest score in the array */
int findLowest(const int *scores, int count) {
  int lowest = scores[0];
  int i;

  for (i = 1; i < count; i++) {
    if (scores[i] < lowest) {
      lowest = scores[i];
    }
  }
  return lowest;
}

/* Returns the average of all scores (long total avoids overflow on big surveys)
 */
double calculateAverage(const int *scores, int count) {
  long total = 0;
  int i;

  for (i = 0; i < count; i++) {
    total += scores[i];
  }
  return (double)total / count;
}

/* Prints a row of dashes */
void printLine(void) {
  int i;

  for (i = 0; i < LINE_WIDTH; i++) {
    printf("-");
  }
  printf("\n");
}

/* Prints the formatted summary report */
void printReport(const int *scores, int count) {
  printf("\n");
  printLine();
  printf("Insight Market Research Group\n");
  printf("Survey Summary Report\n");
  printLine();
  printf("Survey Responses : %d\n", count);
  printf("Highest Score    : %d\n", findHighest(scores, count));
  printf("Lowest Score     : %d\n", findLowest(scores, count));
  printf("Average Score    : %.2f\n", calculateAverage(scores, count));
  printf("\n");
}
