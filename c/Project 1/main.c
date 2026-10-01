#include <stdio.h>
#include <string.h>

int main(void) {
  const char COURSE_TITLE[] = "Student Information Management System";
  const char PROGRAMMER_NAME[] = "Jane Smith";
  const char VERSION_NUMBER[] = "4.0";
  const char FILE_NAME[] = "student_record.txt";

  enum { NUM_COURSES = 5 };

  enum AcademicStanding {
    HONORS,
    GOOD_STANDING,
    ACADEMIC_PROBATION,
    ACADEMIC_SUSPENSION
  } academicStanding;

  long studentID;
  char studentName[50];
  double currentGPA;
  int grades[NUM_COURSES];
  double averageGrade;
  int highestGrade;
  int lowestGrade;
  char gradeInputEnding;
  int gradeInputResult;
  const char *academicStandingText;
  FILE *studentFile;
  long savedStudentID;
  char savedStudentName[50];
  double savedGPA;
  char savedAcademicStanding[30];
  int savedGrades[NUM_COURSES];
  int verificationPassed = 0;
  char verificationAnswer;

  printf("----------------------------------------\n");
  printf("%s\n", COURSE_TITLE);
  printf("Version %s\n", VERSION_NUMBER);
  printf("Programmer: %s\n", PROGRAMMER_NAME);
  printf("\nWelcome to SIMS\n");
  printf("----------------------------------------\n\n");

  printf("Enter Student ID: ");
  scanf("%ld", &studentID);
  getchar();

  printf("Enter Student Name: ");
  scanf("%49[^\n]", studentName);
  getchar();

  printf("Enter Current GPA: ");
  scanf("%lf", &currentGPA);

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

  switch (academicStanding) {
  case HONORS:
    academicStandingText = "Honors";
    break;
  case GOOD_STANDING:
    academicStandingText = "Good Standing";
    break;
  case ACADEMIC_PROBATION:
    academicStandingText = "Academic Probation";
    break;
  default:
    academicStandingText = "Academic Suspension";
    break;
  }

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

  averageGrade =
      (grades[0] + grades[1] + grades[2] + grades[3] + grades[4]) / 5.0;

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

  studentFile = fopen(FILE_NAME, "w");
  if (studentFile == NULL) {
    printf("\nERROR\n");
    printf("Unable to open %s for writing.\n", FILE_NAME);
    return 1;
  }

  fprintf(studentFile, "%ld\n", studentID);
  fprintf(studentFile, "%s\n", studentName);
  fprintf(studentFile, "%.2f\n", currentGPA);
  fprintf(studentFile, "%s\n", academicStandingText);
  fprintf(studentFile, "%d\n", grades[0]);
  fprintf(studentFile, "%d\n", grades[1]);
  fprintf(studentFile, "%d\n", grades[2]);
  fprintf(studentFile, "%d\n", grades[3]);
  fprintf(studentFile, "%d\n", grades[4]);

  if (fclose(studentFile) != 0) {
    printf("\nERROR\n");
    printf("Unable to close %s.\n", FILE_NAME);
    return 1;
  }

  printf("\nStudent information saved to %s\n", FILE_NAME);

  studentFile = fopen(FILE_NAME, "r");
  if (studentFile == NULL) {
    printf("\nERROR\n");
    printf("Unable to open %s for reading.\n", FILE_NAME);
    return 1;
  }

  if (fscanf(studentFile, "%ld", &savedStudentID) != 1) {
    printf("\nERROR\n");
    printf("Unable to read student ID from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 1;
  }
  fscanf(studentFile, " \n");
  if (fscanf(studentFile, "%49[^\n]", savedStudentName) != 1) {
    printf("\nERROR\n");
    printf("Unable to read student name from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 1;
  }
  fscanf(studentFile, " \n");
  if (fscanf(studentFile, "%lf", &savedGPA) != 1) {
    printf("\nERROR\n");
    printf("Unable to read GPA from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 1;
  }
  fscanf(studentFile, " \n");
  if (fscanf(studentFile, "%29[^\n]", savedAcademicStanding) != 1) {
    printf("\nERROR\n");
    printf("Unable to read academic standing from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 1;
  }
  fscanf(studentFile, " \n");
  if (fscanf(studentFile, "%d", &savedGrades[0]) != 1) {
    printf("\nERROR\n");
    printf("Unable to read course grade 1 from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 1;
  }
  if (fscanf(studentFile, "%d", &savedGrades[1]) != 1) {
    printf("\nERROR\n");
    printf("Unable to read course grade 2 from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 1;
  }
  if (fscanf(studentFile, "%d", &savedGrades[2]) != 1) {
    printf("\nERROR\n");
    printf("Unable to read course grade 3 from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 1;
  }
  if (fscanf(studentFile, "%d", &savedGrades[3]) != 1) {
    printf("\nERROR\n");
    printf("Unable to read course grade 4 from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 1;
  }
  if (fscanf(studentFile, "%d", &savedGrades[4]) != 1) {
    printf("\nERROR\n");
    printf("Unable to read course grade 5 from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 1;
  }

  if (fclose(studentFile) != 0) {
    printf("\nERROR\n");
    printf("Unable to close %s after reading.\n", FILE_NAME);
    return 1;
  }

  printf("\nRecovered Student Record\n");
  printf("Student ID   : %ld\n", savedStudentID);
  printf("Student Name : %s\n", savedStudentName);
  printf("Current GPA : %.2f\n", savedGPA);
  printf("Academic Standing : %s\n", savedAcademicStanding);
  printf("----------------------------------------\n");
  printf("Course 1 : %d\n", savedGrades[0]);
  printf("Course 2 : %d\n", savedGrades[1]);
  printf("Course 3 : %d\n", savedGrades[2]);
  printf("Course 4 : %d\n", savedGrades[3]);
  printf("Course 5 : %d\n", savedGrades[4]);
  printf("----------------------------------------\n");

  if (savedStudentID == studentID && strcmp(savedStudentName, studentName) == 0 &&
      savedGPA >= currentGPA - 0.005 && savedGPA <= currentGPA + 0.005 &&
      strcmp(savedAcademicStanding, academicStandingText) == 0) {
    verificationPassed = 1;
  }

  if (savedGrades[0] != grades[0] || savedGrades[1] != grades[1] ||
      savedGrades[2] != grades[2] || savedGrades[3] != grades[3] ||
      savedGrades[4] != grades[4]) {
    verificationPassed = 0;
  }

  printf("Does the recovered information match the original record? (Y/N): ");
  scanf(" %c", &verificationAnswer);
  getchar();

  if (verificationAnswer == 'Y' || verificationAnswer == 'y') {
    verificationPassed = 1;
  }

  printf("\nVerification Result: ");
  if (verificationPassed == 1) {
    printf("PASS\n");
  } else {
    printf("FAIL\n");
  }

  printf("\nStudent Summary\n");
  printf("Student ID   : %ld\n", studentID);
  printf("Student Name : %s\n", studentName);
  printf("Current GPA  : %.2f\n", currentGPA);
  printf("Academic Standing : %s\n", academicStandingText);
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

  return 0;
}
