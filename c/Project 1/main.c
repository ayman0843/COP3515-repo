#include <stdbool.h>
#include <stdio.h>

int main(void) {
  /* Constants */
  const char COURSE_TITLE[] = "Student Information Management System";
  const char PROGRAMMER_NAME[] = "Jane Smith";
  const char VERSION_NUMBER[] = "2.0";

  /* Named constant for the number of courses, using an enumeration */
  enum { NUM_COURSES = 5 };

  /* Variables to hold student data (from CCR-001) */
  long studentID;
  char studentName[50];
  double currentGPA;

  /* Array to hold the five course grades (new in CCR-002) */
  int grades[NUM_COURSES];

  /* Variables to hold the grade summary calculations */
  double averageGrade;
  int highestGrade;
  int lowestGrade;

  /* Boolean variable (demonstrates required concept) */
  bool dataEntered = false;

  /* ---- Program Header ---- */
  printf("----------------------------------------\n");
  printf("%s\n", COURSE_TITLE);
  printf("Version %s\n", VERSION_NUMBER);
  printf("Programmer: %s\n", PROGRAMMER_NAME);
  printf("\nWelcome to SIMS\n");
  printf("----------------------------------------\n\n");

  /* ---- Student Data Entry (CCR-001) ---- */
  printf("Enter Student ID: ");
  scanf("%ld", &studentID);
  getchar(); /* clears the leftover newline left behind by scanf */

  printf("Enter Student Name: ");
  fgets(studentName, sizeof(studentName),
        stdin); /* reads full name, including spaces */

  printf("Enter Current GPA: ");
  scanf("%lf", &currentGPA);

  /* ---- Course Grade Entry (CCR-002) ---- */
  printf("\nCourse Grades\n");

  printf("Enter grade for Course 1: ");
  scanf("%d", &grades[0]);

  printf("Enter grade for Course 2: ");
  scanf("%d", &grades[1]);

  printf("Enter grade for Course 3: ");
  scanf("%d", &grades[2]);

  printf("Enter grade for Course 4: ");
  scanf("%d", &grades[3]);

  printf("Enter grade for Course 5: ");
  scanf("%d", &grades[4]);

  dataEntered = true;

  /* ---- Grade Calculations ---- */

  /* Average grade */
  averageGrade =
      (grades[0] + grades[1] + grades[2] + grades[3] + grades[4]) / 5.0;

  /* Highest and lowest grade, found using selection statements (no loops) */
  highestGrade = grades[0];
  lowestGrade = grades[0];

  if (grades[1] > highestGrade) {
    highestGrade = grades[1];
  }
  if (grades[1] < lowestGrade) {
    lowestGrade = grades[1];
  }

  if (grades[2] > highestGrade) {
    highestGrade = grades[2];
  }
  if (grades[2] < lowestGrade) {
    lowestGrade = grades[2];
  }

  if (grades[3] > highestGrade) {
    highestGrade = grades[3];
  }
  if (grades[3] < lowestGrade) {
    lowestGrade = grades[3];
  }

  if (grades[4] > highestGrade) {
    highestGrade = grades[4];
  }
  if (grades[4] < lowestGrade) {
    lowestGrade = grades[4];
  }

  /* ---- Formatted Summary Output ---- */
  if (dataEntered) {
    printf("\nStudent Summary\n");
    printf("Student ID   : %ld\n", studentID);
    printf("Student Name : %s",
           studentName); /* fgets already keeps the trailing newline */
    printf("Current GPA  : %.2f\n", currentGPA);

    printf("----------------------------------------\n");
    printf("Course Grades\n");
    printf("Course 1 : %d\n", grades[0]);
    printf("Course 2 : %d\n", grades[1]);
    printf("Course 3 : %d\n", grades[2]);
    printf("Course 4 : %d\n", grades[3]);
    printf("Course 5 : %d\n", grades[4]);
    printf("----------------------------------------\n");

    printf("Average Grade : %.2f\n", averageGrade);
    printf("Highest Grade : %d\n", highestGrade);
    printf("Lowest Grade  : %d\n", lowestGrade);
  }

  return 0;
}
