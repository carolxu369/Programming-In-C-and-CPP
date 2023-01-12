#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("The file doesn't exist.");
    return NULL;
  }

  kvarray_t * kvpair = malloc(sizeof(*kvpair));
  if (kvpair == NULL) {
    perror("No enough space for malloc.");
    return NULL;
  }

  kvpair->kvarray = NULL;
  kvpair->num = 0;

  char * line = NULL;
  size_t sz = 0;
  //ssize_t len = 0;
  size_t idx = 0;

  while (getline(&line, &sz, f) >= 0) {
    kvpair->num++;
    kvpair->kvarray = realloc(kvpair->kvarray, kvpair->num * sizeof(*kvpair->kvarray));
    if (kvpair->kvarray == NULL) {
      perror("No enough space for realloc.");
      return NULL;
    }
    kvpair_t * kv = malloc(sizeof(*kv));
    kv->key = line;
    char * p = strchr(kv->key, '=');
    if (p != NULL) {
      *p = '\0';
    }
    p += 1;

    kv->value = p;
    char * q = strchr(kv->value, '\n');
    if (q != NULL) {
      *q = '\0';
    }

    kvpair->kvarray[idx] = kv;
    idx++;
    line = NULL;
  }
  fclose(f);
  free(line);
  return kvpair;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->num; i++) {
    free(pairs->kvarray[i]->key);
    // free(pairs->kvarray[i]->value);
    free(pairs->kvarray[i]);
  }

  free(pairs->kvarray);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->num; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvarray[i]->key, pairs->kvarray[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  char * result = NULL;
  for (size_t i = 0; i < pairs->num; i++) {
    if (strcmp(pairs->kvarray[i]->key, key) == 0) {
      result = pairs->kvarray[i]->value;
    }
  }

  return result;
}
