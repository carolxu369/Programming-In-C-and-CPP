#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file: ");
    return EXIT_FAILURE;
  }

  char matrix[10][10]; /*= {{'a','a','a','a','a','a','a','a','a','a'},
                         {'a','a','a','a','a','a','a','a','a','a'},
                         {'a','a','a','a','a','a','a','a','a','a'},
                         {'a','a','a','a','a','a','a','a','a','a'},
                         {'a','a','a','a','a','a','a','a','a','a'},
                         {'a','a','a','a','a','a','a','a','a','a'},
                         {'a','a','a','a','a','a','a','a','a','a'},
                         {'a','a','a','a','a','a','a','a','a','a'},
                         {'a','a','a','a','a','a','a','a','a','a'},
                         {'a','a','a','a','a','a','a','a','a','a'}};*/

  // check the input file valid
  char line[12];
  int count_line = 0;
  int count_char = 0;
  while (fgets(line, 12, f) != NULL) {
    if (strchr(line, '\n') == NULL) {
      perror("Line is too long: ");
      return EXIT_FAILURE;
    }

    for (int i = 0; i < 12; i++) {
      if ((line[i] != '\n') && (line[i] != '\0')) {
        count_char += 1;
      }
      else {
        break;
      }
    }

    //printf("line %d is %c\n", idx, line[idx]);

    if (count_char < 10) {
      perror("Line is too short: ");
      return EXIT_FAILURE;
    }

    count_line += 1;
    if (count_line <= 10) {
      for (int i = 0; i < 10; i++) {
        if (isprint(line[i]) == 0) {
          perror("The char is not printable: ");
          return EXIT_FAILURE;
        }
        matrix[count_line - 1][i] = line[i];
      }
    }
  }

  if (count_line > 10) {
    perror("Too many lines: ");
    return EXIT_FAILURE;
  }

  else if (count_line < 10) {
    perror("Less lines: ");
    return EXIT_FAILURE;
  }

  //int c;

  /*for (int i=0; i<10; i++){
    for (int j=0; j<11; j++){
      c = fgetc(f);
      //if (isprint(c) == 0){
        //printf("The char is not printable.\n");
        //return EXIT_FAILURE;
      //}
      if (c == '\n'){
        continue;
      }
      else{
        matrix[i][j] = c;
      }
    }
  }*/

  for (int i = 0; i < 10; i++) {
    for (int j = 9; j >= 0; j--) {
      printf("%c", matrix[j][i]);
    }
    printf("\n");
  }

  fclose(f);
  return EXIT_SUCCESS;
}
