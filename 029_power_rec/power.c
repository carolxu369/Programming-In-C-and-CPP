#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y) {
  if (x == 0 && y == 0) {
    return 1;
  }
  else if (x != 0 && y == 0) {
    return 1;
  }
  else if (x == 0 && y != 0) {
    return 0;
  }

  return x * power(x, y - 1);
}
