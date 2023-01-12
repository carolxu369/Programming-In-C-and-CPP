#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * add = ".counts";
  size_t size = strlen(inputName) + strlen(add);
  char * result = malloc((size + 1) * sizeof(*result));
  strcpy(result, inputName);
  strcat(result, add);
  return result;
}
