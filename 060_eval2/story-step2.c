#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"
// use the header files from eval 1

// story-step 2
int main(int argc, char ** argv) {
  // check whether we only have one command line argument
  if (argc != 2) {
    perror("The number of command line arguments entered is wrong.\n");
    exit(EXIT_FAILURE);
  }

  // open the file for reading and check the corresponding error
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("The file cannot be opened.\n");
    exit(EXIT_FAILURE);
  }

  catarray_t * cat_array = get_catarray_t(f);

  printWords(cat_array);

  // free part
  free_catarray_t(cat_array);

  // check whether the file is closed or not
  if (fclose(f) != 0) {
    perror("The file cannot be closed.\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
