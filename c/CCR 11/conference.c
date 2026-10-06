#include <stdio.h>
#include <string.h>

#define LINE_WIDTH 40

/* Prints a row of dashes as a divider */
void printLine(void) {
  int i;
  for (i = 0; i < LINE_WIDTH; i++) {
    printf("-");
  }
  printf("\n");
}

/* Prints the report header */
void printHeader(void) {
  printLine();
  printf("National Technology Conference\n");
  printf("Presenter Summary\n");
  printLine();
}

/* Prints each presenter as a numbered list */
void printPresenters(int count, char *names[]) {
  int i;
  printf("Presenters\n");
  for (i = 0; i < count; i++) {
    printf("%d. %s\n", i + 1, names[i]);
  }
}

/* Returns the index of the presenter with the most characters.
   If there is a tie, the first one found is kept. */
int findLongestIndex(int count, char *names[]) {
  int i;
  int longestIndex = 0;

  for (i = 1; i < count; i++) {
    if (strlen(names[i]) > strlen(names[longestIndex])) {
      longestIndex = i;
    }
  }
  return longestIndex;
}

int main(int argc, char *argv[]) {
  int count = argc - 1;    /* argv[0] is the program name */
  char **names = argv + 1; /* names[0] is the first presenter */
  int longestIndex;

  if (count < 1) {
    printf("Usage: %s \"Presenter 1\" \"Presenter 2\" ...\n", argv[0]);
    return 1;
  }

  longestIndex = findLongestIndex(count, names);

  printHeader();
  printPresenters(count, names);
  printLine();
  printf("Total Presenters : %d\n", count);
  printf("Longest Name : %s\n", names[longestIndex]);
  printf("Characters : %d\n", (int)strlen(names[longestIndex]));

  return 0;
}
