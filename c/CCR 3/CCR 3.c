#include <stdio.h>

int main(void) {
  int age;
<<<<<<< HEAD
  int dayChoice;

  printf("Enter customer's age: ");
  scanf("%d", &age);

  printf("Enter day type (1 = Weekday, 2 = Weekend): ");
  scanf("%d", &dayChoice);

  printf("----------------------------------------\n");
  printf("Grand Cinema Theater\n");
  printf("Ticket Classification\n");
  printf("----------------------------------------\n");

  /* Validate age first. An "impossible" age is negative or
     unreasonably large (over 120). Invalid day input is
     also rejected so a ticket category is never guessed. */
  if (age < 0 || age > 120) {
    printf("Error\n");
    printf("The customer's age is invalid.\n");
    printf("Please enter a valid age.\n");
  } else if (dayChoice != 1 && dayChoice != 2) {
    printf("Error\n");
    printf("The day type entered is invalid.\n");
    printf("Please enter 1 for Weekday or 2 for Weekend.\n");
  } else {
    /* Age is valid at this point (0-120), so determine category. */
    printf("Customer Age : %d\n", age);

    if (dayChoice == 1)
      printf("Day Type     : Weekday\n");
    else
      printf("Day Type     : Weekend\n");

    if (age <= 12)
      printf("Ticket Type  : Child Ticket\n");
    else if (age <= 64)
      printf("Ticket Type  : Adult Ticket\n");
    else
      printf("Ticket Type  : Senior Ticket\n");
=======
  char dayType;

  printf("Enter Customer Age: ");
  if (scanf("%d", &age) != 1 || age < 0 || age > 120) {
    printf("\n----------------------------------------\n");
    printf("Grand Cinema Theater\n");
    printf("Ticket Classification\n");
    printf("----------------------------------------\n");
    printf("Error\n");
    printf("The customer's age is invalid.\n");
    printf("Please enter a valid age.\n");
    return 0;
  }

  printf("Enter Day Type (W = Weekday, E = Weekend): ");
  if (scanf(" %c", &dayType) != 1 ||
      (dayType != 'W' && dayType != 'w' && dayType != 'E' && dayType != 'e')) {
    printf("\n----------------------------------------\n");
    printf("Grand Cinema Theater\n");
    printf("Ticket Classification\n");
    printf("----------------------------------------\n");
    printf("Error\n");
    printf("The day type is invalid.\n");
    printf("Please enter W for Weekday or E for Weekend.\n");
    return 0;
  }

  printf("\n----------------------------------------\n");
  printf("Grand Cinema Theater\n");
  printf("Ticket Classification\n");
  printf("----------------------------------------\n");
  printf("Customer Age : %d\n", age);
  if (dayType == 'W' || dayType == 'w') {
    printf("Day Type : Weekday\n");
  } else {
    printf("Day Type : Weekend\n");
  }

  if (age <= 12) {
    printf("Ticket Type : Child Ticket\n");
  } else if (age <= 64) {
    printf("Ticket Type : Adult Ticket\n");
  } else {
    printf("Ticket Type : Senior Ticket\n");
>>>>>>> 6e6beeb (ccr3)
  }

  return 0;
}
