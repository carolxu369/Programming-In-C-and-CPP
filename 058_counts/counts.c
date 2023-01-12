#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->array_str = NULL;
  counts->len = 0;
  counts->un_name = 0;
  return counts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->un_name++;
    return;
  }

  for (size_t i = 0; i < c->len; i++) {
    if (strcmp(c->array_str[i].str, name) == 0) {
      c->array_str[i].count++;
      return;
    }
  }
  // if it's a new str
  c->len++;
  c->array_str = realloc(c->array_str, c->len * sizeof(*c->array_str));
  one_count_t new_str;
  new_str.str = strdup(name);
  new_str.count = 1;
  c->array_str[c->len - 1] = new_str;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->len; i++) {
    fprintf(outFile, "%s: %d\n", c->array_str[i].str, c->array_str[i].count);
  }

  if (c->un_name > 0) {
    fprintf(outFile, "<unknown> : %d\n", c->un_name);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->len; i++) {
    free(c->array_str[i].str);
  }
  free(c->array_str);
  free(c);
}
