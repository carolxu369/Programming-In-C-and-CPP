#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if ((n == 0) || (n == 1)) {
    return n;
  }
  size_t ans = 1;
  size_t count = 1;
  int curr_elem = array[0];

  for (int i = 1; i < n; i++) {
    if (array[i] > curr_elem) {
      count += 1;
      if (count >= ans) {
        ans = count;
      }
    }
    else {
      count = 1;
    }

    curr_elem = array[i];
  }

  return ans;
}
