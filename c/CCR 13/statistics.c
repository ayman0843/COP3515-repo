#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUMBER_COUNT 10
#define LINE "----------------------------------------"

/* Fills the array with a repeatable sequence of numbers. */
void generate_numbers(int numbers[], int count) {
  int i;
  for (i = 0; i < count; i++) {
    numbers[i] = (i * 17 + 5) % 43;
  }
}

/* Second process: receive numbers, calculate statistics, send results back. */
int run_child(int data_fd, int result_fd) {
  int count;
  int numbers[NUMBER_COUNT];
  int results[3]; /* results[0] = count, [1] = min, [2] = max */
  int sum = 0;
  int i;
  double average;

  printf("Child Process Started\n");
  printf("Receiving Numbers...\n");

  if (read(data_fd, &count, sizeof(count)) != sizeof(count) || count < 1 ||
      count > NUMBER_COUNT) {
    printf("Child Error: could not receive a valid count\n");
    return 1;
  }

  if (read(data_fd, numbers, count * sizeof(int)) != count * sizeof(int)) {
    printf("Child Error: could not receive the numbers\n");
    return 1;
  }

  printf("Calculating Statistics...\n");

  results[0] = count;
  results[1] = numbers[0];
  results[2] = numbers[0];

  for (i = 0; i < count; i++) {
    if (numbers[i] < results[1]) {
      results[1] = numbers[i];
    }
    if (numbers[i] > results[2]) {
      results[2] = numbers[i];
    }
    sum = sum + numbers[i];
  }

  average = (double)sum / count;

  write(result_fd, results, sizeof(results));
  write(result_fd, &average, sizeof(average));

  printf("Child Process Finished\n");
  return 0;
}

/* Displays the calculated statistics in a readable report. */
void print_report(int results[], double average) {
  printf("%s\n", LINE);
  printf("Count   : %d\n", results[0]);
  printf("Minimum : %d\n", results[1]);
  printf("Maximum : %d\n", results[2]);
  printf("Average : %.2f\n", average);
  printf("%s\n", LINE);
}

int main(void) {
  int data_pipe[2];   /* parent -> child: the generated numbers */
  int result_pipe[2]; /* child -> parent: the calculated statistics */
  int numbers[NUMBER_COUNT];
  int count = NUMBER_COUNT;
  int results[3];
  double average;
  int status;
  int child_result;
  pid_t pid;

  printf("%s\n", LINE);
  printf("Data Analytics Solutions\n");
  printf("Statistics Processing\n");
  printf("%s\n", LINE);

  if (pipe(data_pipe) == -1 || pipe(result_pipe) == -1) {
    printf("Error: could not create pipes\n");
    return 1;
  }

  printf("Parent Process Started\n");
  fflush(stdout); /* avoid duplicated buffered output after fork() */

  pid = fork();

  if (pid < 0) {
    printf("Error: could not create child process\n");
    return 1;
  }

  if (pid == 0) {
    /* ---------- CHILD PROCESS ---------- */
    close(data_pipe[1]);   /* child only reads numbers  */
    close(result_pipe[0]); /* child only writes results */

    child_result = run_child(data_pipe[0], result_pipe[1]);

    close(data_pipe[0]);
    close(result_pipe[1]);
    return child_result;
  }

  /* ---------- PARENT PROCESS ---------- */
  close(data_pipe[0]);   /* parent only writes numbers */
  close(result_pipe[1]); /* parent only reads results  */

  printf("Generating Numbers...\n");
  generate_numbers(numbers, count);

  write(data_pipe[1], &count, sizeof(count));
  write(data_pipe[1], numbers, count * sizeof(int));
  close(data_pipe[1]);
  printf("Numbers Sent Successfully\n");
  fflush(stdout);

  wait(&status); /* wait for the child to finish */

  if (status != 0 ||
      read(result_pipe[0], results, sizeof(results)) != sizeof(results) ||
      read(result_pipe[0], &average, sizeof(average)) != sizeof(average)) {
    printf("Error: statistics were not received from the child\n");
    close(result_pipe[0]);
    return 1;
  }
  close(result_pipe[0]);

  print_report(results, average);

  printf("Parent Process Finished\n");
  return 0;
}
