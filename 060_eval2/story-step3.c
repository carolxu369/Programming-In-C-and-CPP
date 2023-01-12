#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"
// use the header files from eval 1

// story-step 3
int main(int argc, char ** argv) {
  // check whether we only have two command line arguments
  if (argc != 3) {
    perror("The number of command line arguments entered is wrong.\n");
    exit(EXIT_FAILURE);
  }

  // open the file for reading and check the corresponding error
  FILE * f_word = fopen(argv[1], "r");
  if (f_word == NULL) {
    perror("The file for category/word cannot be opened.\n");
    exit(EXIT_FAILURE);
  }

  FILE * f_story = fopen(argv[2], "r");
  if (f_story == NULL) {
    perror("The file for story cannot be opened.\n");
    exit(EXIT_FAILURE);
  }

  print_story(f_word, f_story);

  // check whether the file is closed or not
  if (fclose(f_word) != 0) {
    perror("The file cannot be closed.\n");
    exit(EXIT_FAILURE);
  }

  if (fclose(f_story) != 0) {
    perror("The file cannot be closed.\n");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
