#include <stdio.h>

#define REPORT_LINE_LONG "----------------------------------------"
#define REPORT_LINE_SHORT "-------------------------------"

/* ---------- Function prototypes ---------- */
void print_prompt(int which);
int read_dimension(int which, double *value);
double calculate_volume(double length, double width, double height);
double calculate_surface_area(double length, double width, double height);
void print_report(double length, double width, double height, double volume,
                  double surface_area);

int main(void) {
  double length = 0.0;
  double width = 0.0;
  double height = 0.0;
  double volume;
  double surface_area;

  /* 1 = length, 2 = width, 3 = height */
  if (!read_dimension(1, &length) || !read_dimension(2, &width) ||
      !read_dimension(3, &height)) {
    printf("\nInput ended before all dimensions were entered.\n");
    return 1;
  }

  volume = calculate_volume(length, width, height);
  surface_area = calculate_surface_area(length, width, height);

  print_report(length, width, height, volume, surface_area);

  return 0;
}

/* Prints the prompt text for the requested dimension. */
void print_prompt(int which) {
  switch (which) {
  case 1:
    printf("Enter the box length: ");
    break;
  case 2:
    printf("Enter the box width: ");
    break;
  case 3:
    printf("Enter the box height: ");
    break;
  default:
    printf("Enter a value: ");
    break;
  }
}

/*
 * Asks for one dimension and repeats until the employee enters a number
 * greater than zero. The valid number is stored through the pointer.
 * Returns 1 on success, or 0 if input ended (end-of-file).
 */
int read_dimension(int which, double *value) {
  int ch;
  int valid = 0;

  while (!valid) {
    print_prompt(which);

    if (scanf("%lf", value) == 1) {
      if (*value > 0.0) {
        valid = 1;
      } else {
        printf("Error: the dimension must be greater than 0.\n");
      }
    } else {
      /* Not a number (or end of input) */
      ch = getchar();
      if (ch == EOF) {
        return 0;
      }
      printf("Error: please enter a numeric value.\n");
    }

    /* Throw away anything left on the line, including the newline */
    ch = getchar();
    while (ch != '\n' && ch != EOF) {
      ch = getchar();
    }
  }

  return 1;
}

/* Volume = length x width x height */
double calculate_volume(double length, double width, double height) {
  return length * width * height;
}

/* Surface area = 2 x (length*width + length*height + width*height) */
double calculate_surface_area(double length, double width, double height) {
  return 2.0 * ((length * width) + (length * height) + (width * height));
}

/* Prints the formatted report shown in the customer's examples. */
void print_report(double length, double width, double height, double volume,
                  double surface_area) {
  printf("\n");
  printf("%s\n", REPORT_LINE_LONG);
  printf("Atlantic Shipping & Logistics\n");
  printf("Package Measurement Report\n");
  printf("%s\n", REPORT_LINE_LONG);
  printf("Length       : %.2f\n", length);
  printf("Width        : %.2f\n", width);
  printf("Height       : %.2f\n", height);
  printf("%s\n", REPORT_LINE_SHORT);
  printf("Volume       : %.2f cubic units\n", volume);
  printf("Surface Area : %.2f square units\n", surface_area);
}
