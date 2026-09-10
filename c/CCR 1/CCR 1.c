#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* Helper function to clear the input buffer */
void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

int main() {
  char name[31];
  char temp_name[100];
  int age;
  float fee;
  int validInput;

  /* --- Employee Input with Validation --- */

  // Name Validation: Restricts input to max 30 characters and only
  // letters/apostrophes
  while (1) {
    printf("Enter First Name (max 30 characters, no special characters except "
           "'): ");
    if (scanf("%99s", temp_name) == 1) {
      clearBuffer(); // Clears any subsequent words or trailing newlines

      int len = strlen(temp_name);

      // Check if the name exceeds 30 characters
      if (len > 30) {
        printf("Invalid input. Name cannot be longer than 30 characters. Try "
               "again.\n");
        continue;
      }

      // Check for special characters (allowing only letters and apostrophes)
      int hasSpecialChar = 0;
      for (int i = 0; i < len; i++) {
        if (!isalpha(temp_name[i]) && temp_name[i] != '\'') {
          hasSpecialChar = 1;
          break;
        }
      }

      if (hasSpecialChar) {
        printf("Invalid input. Name cannot contain special characters (except "
               "'). Try again.\n");
        continue;
      }

      // If both checks pass, copy the valid name to the main variable
      strcpy(name, temp_name);
      break;
    }
  }

  // Age Validation: Ensures a whole number within a realistic human range
  while (1) {
    printf("Enter Age (whole number): ");
    validInput = scanf("%d", &age);

    if (validInput == 1 && age >= 18 && age <= 90) {
      clearBuffer();
      break;
    } else {
      printf("Invalid input. Please enter a realistic whole number (18-90).\n");
      if (validInput != 1) {
        clearBuffer(); // Clear non-numeric characters from the buffer
      }
    }
  }

  // Fee Validation: Ensures a non-negative numerical value[cite: 1]
  while (1) {
    printf("Enter Monthly Fee: ");
    validInput = scanf("%f", &fee);

    if (validInput == 1 && fee >= 0.0) {
      clearBuffer();
      break;
    } else {
      printf("Invalid input. Please enter a valid non-negative number.\n");
      if (validInput != 1) {
        clearBuffer();
      }
    }
  }

  /* --- Expected Output --- */
  printf("\n");
  printf("Tampa Fitness Center\n");
  printf("Membership Receipt\n");
  printf("Customer: %s\n", name);
  printf("Age: %d\n", age);
  printf("Monthly Fee: $%.2f\n", fee);

  /* Determine if the customer qualifies for the Senior Program[cite: 1] */
  if (age >= 65) {
    printf("Status: Senior Program\n");
  } else {
    printf("Status: Standard Membership\n");
  }

  printf("Thank you for joining!\n");

  return 0;
}
