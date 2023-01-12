#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run_check(int * array, size_t n, size_t expected_answer) {
  if (maxSeq(array, n) != expected_answer) {
    printf("Your answer is wrong.");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int array1[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  run_check(array1, 10, 4);
  int array2[] = {0};
  run_check(array2, 1, 1);
  int array3[] = {0, 0, 0, 0, 0};
  run_check(array3, 5, 1);
  int array4[] = {1, 2, 3, 4, 5};
  run_check(array4, 5, 5);
  int array5[] = {5, 4, 3, 2, 1};
  run_check(array5, 5, 1);
  run_check(NULL, 0, 0);
  int array6[] = {-2, -1, 0, 1, 2};
  run_check(array6, 5, 5);
  printf("You succeed in all.");
  return EXIT_SUCCESS;
}
