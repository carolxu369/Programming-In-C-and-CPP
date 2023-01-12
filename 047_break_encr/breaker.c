#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  int dict_count[26] = {0};
  int c;

  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      dict_count[c - 97]++;
    }
  }

  int max = 0;
  int idx = 0;
  for (int i = 0; i < 26; i++) {
    if (dict_count[i] > max) {
      max = dict_count[i];
      idx = i;
    }
  }

  int char_e = 'e' - 97;
  int key = idx - char_e;

  if (key >= 0) {
    printf("%d\n", key);
  }
  else {
    key = key + 26;
    printf("%d\n", key);
  }

  return EXIT_SUCCESS;
}
