#include <stdio.h>
#include <stdlib.h>
struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  for (int i = 1; i <= working.months; i++) {
    printf("Age %3d month %2d you have $%.2f\n", startAge / 12, startAge % 12, initial);
    double ror = initial * working.rate_of_return;
    initial += ror + working.contribution;
    startAge += 1;
  }

  for (int i = 1; i <= retired.months; i++) {
    printf("Age %3d month %2d you have $%.2f\n", startAge / 12, startAge % 12, initial);
    double ror = initial * retired.rate_of_return;
    initial += ror + retired.contribution;
    startAge += 1;
  }
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  int startAge = 327;
  double initial = 21345;
  retirement(startAge, initial, working, retired);
  return EXIT_SUCCESS;
}
