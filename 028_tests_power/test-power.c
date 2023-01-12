#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_answer) {
  if (power(x, y) != expected_answer) {
    printf("Your power calculation is wrong.");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(0, 0, 1);
  run_check(0, 5, 0);
  run_check(5, 0, 1);
  run_check(3, 2, 9);
  run_check(1, 3, 1);
  run_check(-1, 1, -1);
  printf("You succeed in all.");
  return EXIT_SUCCESS;
}
