#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

char ** get_line_list(FILE * input_file, int * count_i) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t linecap;
  size_t i = 0;

  while (getline(&curr, &linecap, input_file) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  count_i[0] = i;

  return lines;
}

void sort_print(char ** lines, int count) {
  sortData(lines, count);
  for (int i = 0; i < count; i++) {
    printf("%s", lines[i]);
    free(lines[i]);
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    FILE * f = stdin;
    if (f == NULL) {
      perror("Could not open file");
      return EXIT_FAILURE;
    }
    int count[1] = {0};
    char ** file_lines = get_line_list(f, count);
    sort_print(file_lines, count[0]);
    free(file_lines);
    if (fclose(f) != 0) {
      perror("Failed to close the input file!");
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }

  else {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
      }

      int count[1] = {0};
      char ** file_lines = get_line_list(f, count);
      sort_print(file_lines, count[0]);
      free(file_lines);

      if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
      }
    }
    return EXIT_SUCCESS;
  }
}
