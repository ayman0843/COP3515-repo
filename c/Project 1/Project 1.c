#include <stdbool.h>
#include <stdio.h>

int main(void) {
  /* Constants */
  const char COURSE_TITLE[] = "Student Information Management System";
  const char PROGRAMMER_NAME[] = "Jane Smith";
  const char VERSION_NUMBER[] = "1.0";

  /* Variables to hold student data */
  long studentID;
  char studentName[50];
  double currentGPA;

  /* Boolean variable (demonstrates required concept) */
  bool dataEntered = false;

  /* ---- Program Header ---- */
  printf("----------------------------------------\n");
  printf("%s\n", COURSE_TITLE);
  printf("Version %s\n", VERSION_NUMBER);
  printf("Programmer: %s\n", PROGRAMMER_NAME);
  printf("\nWelcome to SIMS\n");
  printf("----------------------------------------\n\n");

  /* ---- Data Entry ---- */
  printf("Enter Student ID: ");
  scanf("%ld", &studentID);
  getchar(); /* clears the leftover newline left behind by scanf */

  printf("Enter Student Name: ");
  fgets(studentName, sizeof(studentName),
        stdin); /* reads full name, including spaces */

  printf("Enter Current GPA: ");
  scanf("%lf", &currentGPA);

  dataEntered = true;

  /* ---- Formatted Summary Output ---- */
  if (dataEntered) {
    printf("\nStudent Summary\n");
    printf("Student ID   : %ld\n", studentID);
    printf("Student Name : %s",
           studentName); /* fgets already keeps the trailing newline */
    printf("Current GPA  : %.2f\n", currentGPA);
  }

  return 0;
}
