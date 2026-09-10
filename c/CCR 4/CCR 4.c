#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100

typedef struct {
  char name[64];
  int hours;
} Employee;

static void trimWhitespace(char *text) {
  char *start = text;
  char *end;

  while (*start == ' ' || *start == '\t' || *start == '\r' || *start == '\n') {
    start++;
  }

  if (start != text) {
    memmove(text, start, strlen(start) + 1);
  }

  end = text + strlen(text) - 1;
  while (end >= text &&
         (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n')) {
    *end = '\0';
    end--;
  }
}

static int loadEmployees(const char *filename, Employee employees[],
                         int maxEmployees) {
  FILE *file = fopen(filename, "r");
  char line[256];
  int count = 0;

  if (file == NULL) {
    return -1;
  }

  while (count < maxEmployees && fgets(line, sizeof(line), file) != NULL) {
    char *commaPos;
    char *hoursText;
    int hours;

    commaPos = strchr(line, ',');
    if (commaPos == NULL) {
      continue;
    }

    *commaPos = '\0';
    hoursText = commaPos + 1;

    trimWhitespace(line);
    trimWhitespace(hoursText);

    if (line[0] == '\0' || hoursText[0] == '\0') {
      continue;
    }

    hours = atoi(hoursText);
    strncpy(employees[count].name, line, sizeof(employees[count].name) - 1);
    employees[count].name[sizeof(employees[count].name) - 1] = '\0';
    employees[count].hours = hours;
    count++;
  }

  fclose(file);
  return count;
}

int main(int argc, char *argv[]) {
  const char *filename = (argc > 1) ? argv[1] : "employee_hours.txt";
  Employee employees[MAX_EMPLOYEES];
  int employeeCount;
  int totalHours = 0;
  int mostHoursIndex = 0;
  int fewestHoursIndex = 0;
  int overtimeCount = 0;
  int overtimeTotal = 0;
  int i;
  double averageHours;

  employeeCount = loadEmployees(filename, employees, MAX_EMPLOYEES);
  if (employeeCount == -1) {
    fprintf(stderr, "Error: unable to open '%s'.\n", filename);
    return 1;
  }

  if (employeeCount == 0) {
    printf("No employee data was found in %s.\n", filename);
    return 0;
  }

  for (i = 0; i < employeeCount; i++) {
    totalHours += employees[i].hours;

    if (employees[i].hours > employees[mostHoursIndex].hours) {
      mostHoursIndex = i;
    }

    if (employees[i].hours < employees[fewestHoursIndex].hours) {
      fewestHoursIndex = i;
    }

    if (employees[i].hours > 40) {
      overtimeCount++;
      overtimeTotal += employees[i].hours;
    }
  }

  averageHours = (double)totalHours / employeeCount;

  printf("Employee Hours Report\n");
  printf("====================\n");
  printf("Total employees: %d\n", employeeCount);
  printf("Total hours worked: %d\n", totalHours);
  printf("Average hours per employee: %.2f\n", averageHours);
  printf("Highest hours: %s (%d hours)\n", employees[mostHoursIndex].name,
         employees[mostHoursIndex].hours);
  printf("Lowest hours: %s (%d hours)\n", employees[fewestHoursIndex].name,
         employees[fewestHoursIndex].hours);
  printf("Employees over 40 hours: %d\n", overtimeCount);
  printf("Total overtime hours: %d\n", overtimeTotal);

  printf("\nEmployees working overtime:\n");
  for (i = 0; i < employeeCount; i++) {
    if (employees[i].hours > 40) {
      printf("- %s: %d hours\n", employees[i].name, employees[i].hours);
    }
  }

  return 0;
}
