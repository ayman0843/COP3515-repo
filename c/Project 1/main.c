#include <stdio.h>
#include <string.h>

#define NUM_COURSES 5

enum AcademicStanding {
  HONORS,
  GOOD_STANDING,
  ACADEMIC_PROBATION,
  ACADEMIC_SUSPENSION
};

const char COURSE_TITLE[] = "Student Information Management System";
const char PROGRAMMER_NAME[] = "Jane Smith";
const char VERSION_NUMBER[] = "6.0";
const char FILE_NAME[] = "student_record.txt";

long studentID = 0;
char studentName[50] = "";
double currentGPA = 0.0;
int grades[NUM_COURSES];
double averageGrade = 0.0;
int highestGrade = 0;
int lowestGrade = 0;
char gradeInputEnding;
int gradeInputResult;
const char *academicStandingText = "Not Set";
FILE *studentFile;
long savedStudentID;
char savedStudentName[50] = "";
double savedGPA;
char savedAcademicStanding[30] = "";
int savedGrades[NUM_COURSES];
int verificationPassed = 0;
char verificationAnswer;
int menuChoice = 0;
int studentDataEntered = 0;
int gradesEntered = 0;

void displayProgramHeader(void) {
  printf("----------------------------------------\n");
  printf("%s\n", COURSE_TITLE);
  printf("Version %s\n", VERSION_NUMBER);
  printf("Programmer: %s\n", PROGRAMMER_NAME);
  printf("\nWelcome to SIMS\n");
  printf("----------------------------------------\n\n");
}

void displayMainMenu(void) {
  printf("Student Information Management System\n\n");
  printf("1. Add Student\n");
  printf("2. Display Student\n");
  printf("3. Enter Grades\n");
  printf("4. Save Student Record\n");
  printf("5. Exit Program\n\n");
  printf("Selection: ");
}

int determineAcademicStanding(double gpa) {
  if (gpa >= 3.50) {
    return HONORS;
  } else if (gpa >= 2.00) {
    return GOOD_STANDING;
  } else if (gpa >= 1.00) {
    return ACADEMIC_PROBATION;
  } else {
    return ACADEMIC_SUSPENSION;
  }
}

void setAcademicStandingText(int standing) {
  if (standing == HONORS) {
    academicStandingText = "Honors";
  } else if (standing == GOOD_STANDING) {
    academicStandingText = "Good Standing";
  } else if (standing == ACADEMIC_PROBATION) {
    academicStandingText = "Academic Probation";
  } else {
    academicStandingText = "Academic Suspension";
  }
}

void calculateGradeStatistics(void) {
  averageGrade = (grades[0] + grades[1] + grades[2] + grades[3] + grades[4]) / 5.0;
  highestGrade = grades[0];
  lowestGrade = grades[0];

  for (int i = 1; i < NUM_COURSES; i++) {
    if (grades[i] > highestGrade) {
      highestGrade = grades[i];
    }
    if (grades[i] < lowestGrade) {
      lowestGrade = grades[i];
    }
  }
}

int enterStudentInformation(void) {
  printf("Enter Student ID: ");
  scanf("%ld", &studentID);
  getchar();

  printf("Enter Student Name: ");
  scanf("%49[^\n]", studentName);
  getchar();

  printf("Enter Current GPA: ");
  scanf("%lf", &currentGPA);
  getchar();

  if (currentGPA < 0.00 || currentGPA > 4.00) {
    printf("\nERROR\n");
    printf("Invalid GPA entered.\n");
    printf("GPA must be between 0.00 and 4.00.\n");
    studentDataEntered = 0;
    return 0;
  }

  setAcademicStandingText(determineAcademicStanding(currentGPA));
  studentDataEntered = 1;
  printf("Student information added successfully.\n");
  return 1;
}

void displayStudentReport(void) {
  if (studentDataEntered == 0) {
    printf("No student information has been entered yet.\n");
    return;
  }

  printf("Student Summary\n");
  printf("Student ID   : %ld\n", studentID);
  printf("Student Name : %s\n", studentName);
  printf("Current GPA  : %.2f\n", currentGPA);
  printf("Academic Standing : %s\n", academicStandingText);
  printf("----------------------------------------\n");

  if (gradesEntered == 1) {
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
  } else {
    printf("Grades have not been entered yet.\n");
  }
}

int enterCourseGrades(void) {
  if (studentDataEntered == 0) {
    printf("Please add the student before entering grades.\n");
    return 0;
  }

  printf("\nCourse Grades\n");

  for (int i = 0; i < NUM_COURSES; i++) {
    printf("Enter grade for Course %d: ", i + 1);
    gradeInputResult = scanf("%d%c", &grades[i], &gradeInputEnding);
    if (gradeInputResult != 2 || gradeInputEnding != '\n' || grades[i] < 0 ||
        grades[i] > 100) {
      printf("Invalid course grade. Enter a whole number from 0 to 100.\n");
      gradesEntered = 0;
      return 0;
    }
  }

  calculateGradeStatistics();
  gradesEntered = 1;
  printf("Course grades entered successfully.\n");
  return 1;
}

int readStudentRecord(void) {
  studentFile = fopen(FILE_NAME, "r");
  if (studentFile == NULL) {
    printf("\nERROR\n");
    printf("Unable to open %s for reading.\n", FILE_NAME);
    return 0;
  }

  if (fscanf(studentFile, "%ld", &savedStudentID) != 1) {
    printf("\nERROR\n");
    printf("Unable to read student ID from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 0;
  }
  fscanf(studentFile, " \n");
  if (fscanf(studentFile, "%49[^\n]", savedStudentName) != 1) {
    printf("\nERROR\n");
    printf("Unable to read student name from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 0;
  }
  fscanf(studentFile, " \n");
  if (fscanf(studentFile, "%lf", &savedGPA) != 1) {
    printf("\nERROR\n");
    printf("Unable to read GPA from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 0;
  }
  fscanf(studentFile, " \n");
  if (fscanf(studentFile, "%29[^\n]", savedAcademicStanding) != 1) {
    printf("\nERROR\n");
    printf("Unable to read academic standing from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 0;
  }
  fscanf(studentFile, " \n");
  if (fscanf(studentFile, "%d", &savedGrades[0]) != 1) {
    printf("\nERROR\n");
    printf("Unable to read course grade 1 from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 0;
  }
  if (fscanf(studentFile, "%d", &savedGrades[1]) != 1) {
    printf("\nERROR\n");
    printf("Unable to read course grade 2 from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 0;
  }
  if (fscanf(studentFile, "%d", &savedGrades[2]) != 1) {
    printf("\nERROR\n");
    printf("Unable to read course grade 3 from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 0;
  }
  if (fscanf(studentFile, "%d", &savedGrades[3]) != 1) {
    printf("\nERROR\n");
    printf("Unable to read course grade 4 from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 0;
  }
  if (fscanf(studentFile, "%d", &savedGrades[4]) != 1) {
    printf("\nERROR\n");
    printf("Unable to read course grade 5 from %s.\n", FILE_NAME);
    fclose(studentFile);
    return 0;
  }

  if (fclose(studentFile) != 0) {
    printf("\nERROR\n");
    printf("Unable to close %s after reading.\n", FILE_NAME);
    return 0;
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

  verificationPassed = 1;
  if (savedStudentID != studentID ||
      strcmp(savedStudentName, studentName) != 0 ||
      savedGPA < currentGPA - 0.005 || savedGPA > currentGPA + 0.005 ||
      strcmp(savedAcademicStanding, academicStandingText) != 0) {
    verificationPassed = 0;
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

  return 1;
}

int saveStudentRecord(void) {
  if (studentDataEntered == 0) {
    printf("Please add the student before saving.\n");
    return 0;
  }

  if (gradesEntered == 0) {
    printf("Please enter the five course grades before saving.\n");
    return 0;
  }

  studentFile = fopen(FILE_NAME, "w");
  if (studentFile == NULL) {
    printf("\nERROR\n");
    printf("Unable to open %s for writing.\n", FILE_NAME);
    return 0;
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
    return 0;
  }

  printf("\nStudent information saved to %s\n", FILE_NAME);
  return readStudentRecord();
}

int processMenuSelection(int selection) {
  switch (selection) {
    case 1:
      return enterStudentInformation();
    case 2:
      displayStudentReport();
      return 1;
    case 3:
      return enterCourseGrades();
    case 4:
      return saveStudentRecord();
    case 5:
      printf("Exiting SIMS. Goodbye.\n");
      return 0;
    default:
      printf("Invalid selection. Please choose a valid menu option.\n");
      return 1;
  }
}

int main(void) {
  displayProgramHeader();

  while (menuChoice != 5) {
    displayMainMenu();
    scanf("%d", &menuChoice);
    getchar();
    printf("\n");

    processMenuSelection(menuChoice);
  }

  return 0;
}
