#include <stdbool.h>
#include <stdio.h>

int main(void) {
  /* Constants */
  const char COURSE_TITLE[] = "Student Information Management System";
  const char PROGRAMMER_NAME[] = "Jane Smith";
  const char VERSION_NUMBER[] = "3.0";

  /* Named constant for the number of courses, using an enumeration */
  enum { NUM_COURSES = 5 };

  /* Variables to hold student data (from CCR-001) */
  long studentID;
  char studentName[50];
  double currentGPA;

  /* Academic standing categories (new in CCR-003) */
  enum AcademicStanding {
    HONORS,
    GOOD_STANDING,
    ACADEMIC_PROBATION,
    ACADEMIC_SUSPENSION
  } academicStanding;

  /* Array to hold the five course grades (new in CCR-002) */
  int grades[NUM_COURSES];

  /* Variables to hold the grade summary calculations */
  double averageGrade;
  int highestGrade;
  int lowestGrade;
  char gradeInputEnding;
  int gradeInputResult;

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

  /* ---- GPA Validation and Academic Standing (CCR-003) ---- */
  if (currentGPA < 0.00 || currentGPA > 4.00) {
    printf("\nERROR\n");
    printf("Invalid GPA entered.\n");
    printf("GPA must be between 0.00 and 4.00.\n");
    return 1;
  }

  if (currentGPA >= 3.50) {
    academicStanding = HONORS;
  } else if (currentGPA >= 2.00) {
    academicStanding = GOOD_STANDING;
  } else if (currentGPA >= 1.00) {
    academicStanding = ACADEMIC_PROBATION;
  } else {
    academicStanding = ACADEMIC_SUSPENSION;
  }

  /* ---- Course Grade Entry (CCR-002) ---- */
  printf("\nCourse Grades\n");

  printf("Enter grade for Course 1: ");
  gradeInputResult = scanf("%d%c", &grades[0], &gradeInputEnding);
  if (gradeInputResult != 2 || gradeInputEnding != '\n' || grades[0] < 0 ||
      grades[0] > 100) {
    printf("Invalid course grade. Enter a whole number from 0 to 100.\n");
    return 1;
  }

  printf("Enter grade for Course 2: ");
  gradeInputResult = scanf("%d%c", &grades[1], &gradeInputEnding);
  if (gradeInputResult != 2 || gradeInputEnding != '\n' || grades[1] < 0 ||
      grades[1] > 100) {
    printf("Invalid course grade. Enter a whole number from 0 to 100.\n");
    return 1;
  }

  printf("Enter grade for Course 3: ");
  gradeInputResult = scanf("%d%c", &grades[2], &gradeInputEnding);
  if (gradeInputResult != 2 || gradeInputEnding != '\n' || grades[2] < 0 ||
      grades[2] > 100) {
    printf("Invalid course grade. Enter a whole number from 0 to 100.\n");
    return 1;
  }

  printf("Enter grade for Course 4: ");
  gradeInputResult = scanf("%d%c", &grades[3], &gradeInputEnding);
  if (gradeInputResult != 2 || gradeInputEnding != '\n' || grades[3] < 0 ||
      grades[3] > 100) {
    printf("Invalid course grade. Enter a whole number from 0 to 100.\n");
    return 1;
  }

  printf("Enter grade for Course 5: ");
  gradeInputResult = scanf("%d%c", &grades[4], &gradeInputEnding);
  if (gradeInputResult != 2 || gradeInputEnding != '\n' || grades[4] < 0 ||
      grades[4] > 100) {
    printf("Invalid course grade. Enter a whole number from 0 to 100.\n");
    return 1;
  }

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

    printf("Academic Standing : ");
    if (academicStanding == HONORS) {
      printf("Honors\n");
    } else if (academicStanding == GOOD_STANDING) {
      printf("Good Standing\n");
    } else if (academicStanding == ACADEMIC_PROBATION) {
      printf("Academic Probation\n");
    } else {
      printf("Academic Suspension\n");
    }

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
