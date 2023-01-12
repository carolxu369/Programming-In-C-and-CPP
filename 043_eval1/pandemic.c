#include "pandemic.h"

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// use the header files from MLP 049 rotateMatrix.c

country_t parseLine(char * line) {
  // declare the country_t struct
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  // declare a pointer point to the first element of line
  // declare an idx to update the character in country name
  char * ptr = line;
  int idx = 0;

  // parse the the country name first
  while (*ptr != ',') {
    // check if there is any '\n' or '\0' in the country's name or there is no comma in the input line
    // get the idea of looping pointer position and checking pointer value validity from book example and MLP 049 rotateMatrix.c
    // get the idea of printing error message to the stderr from MLP 049 rotateMatrix.c
    if ((*ptr == '\n') | (*ptr == '\0')) {
      perror("You have an invalid input line.\n");
      exit(EXIT_FAILURE);
    }

    // check whether the characters in the country name are printable
    // get this idea from MLP 049 rotateMatrix.c
    if (isprint(*ptr) == 0) {
      perror("The character in the country name is not printable.\n");
      exit(EXIT_FAILURE);
    }

    // check whether the country name length is out of bound.
    if (idx > 62) {
      perror("The country name is out of the required length.\n");
      exit(EXIT_FAILURE);
    }

    ans.name[idx] = *ptr;
    ans.name[idx + 1] = '\0';
    idx++;
    ptr++;
  }

  // the starting position of the population
  ptr++;
  // declare an array to store the population
  // the size of the array is 21 as the largest length of uint64_t is 20 plus the null terminator
  // get this idea from ans.name
  char number[21];
  number[0] = '\0';
  // declare a new index to record population
  int pop_idx = 0;

  while (*ptr != '\0') {
    // if there are white spaces before the digits start, we ignore those spaces
    if ((number[0] == '\0') && ((*ptr == ' ') | (*ptr == '\t'))) {
      ptr++;
      continue;
    }

    // skip the new line character
    if (*ptr == '\n') {
      ptr++;
      continue;
    }

    // check whether the characters in the poplutaion are digits
    if (isdigit(*ptr) == 0) {
      perror("The input character in the population is not a digit.\n");
      exit(EXIT_FAILURE);
    }

    // check whether the population is out of the largest value of uint64_t
    if (pop_idx > 20) {
      perror("The number of the population is out of required bound.\n");
      exit(EXIT_FAILURE);
    }

    number[pop_idx] = *ptr;
    number[pop_idx + 1] = '\0';
    pop_idx++;
    ptr++;
  }

  // declare an uint64_t to store population
  uint64_t pop_number = 0;
  pop_number = atoi(number);

  // check whether the pop_number is out of uint64_t
  if ((pop_number < 0) | (pop_number > ULONG_MAX)) {
    perror("The number of the population is out of required bound.\n");
    exit(EXIT_FAILURE);
  }

  ans.population = pop_number;

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  // if the n_days is less than 7, then we don't have enough data to calculate the seven-day running average
  // we just do nothing and exit with success
  if (n_days < 7) {
    return;
    exit(EXIT_SUCCESS);
  }

  // declare a double to store the sum of the data
  double sum_case = 0;

  // loop through every seven pieces of data per time, add them up and divided by 7
  // update that value to avg until the end of the data
  // get the idea of looping to assign array values from MLP 049 rotateMatrix.c
  for (size_t i = 0; i < (n_days - 6); i++) {
    for (size_t j = i; j < i + 7; j++) {
      sum_case += data[j];
    }
    avg[i] = sum_case / 7;
    // update sum_case to 0 to record the next seven running average
    sum_case = 0;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  // declare a cumulative sum to record the cumulative number of cases
  double cum_sum = 0;

  // loop through the data and update cum_sum each time by adding the cumulative case with this day number of cases
  // store the cumulative number of cases that day per 100000 people in array cum
  // get the idea of looping to assign array values from MLP 049 rotateMatrix.c
  for (size_t i = 0; i < n_days; i++) {
    cum_sum += data[i];
    cum[i] = cum_sum / pop * 100000;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  // declare a curr_max to record the current max number of daily cases as we loop through all country's time series data
  // declare a max_idx to update the index of country according to curr_max
  unsigned curr_max = 0;
  size_t max_idx = 0;

  // loop through each country's time series data and compare that with curr_max
  // if it's bigger than or equal to, update that value to curr_max
  // and also update the max_idx to that country's index
  // get the idea of looping to assign array values from MLP 049 rotateMatrix.c
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] >= curr_max) {
        curr_max = data[i][j];
        max_idx = i;
      }
    }
  }

  printf("%s has the most daily cases with %u\n", countries[max_idx].name, curr_max);
}
