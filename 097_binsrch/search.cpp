#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low == high) {
    return low;
  }
  else if (low == high - 1) {
    return low;
  }

  int mid = (low + high) / 2;
  int result = f->invoke(mid);

  if (result == 0) {
    return mid;
  }

  else if (result > 0) {
    return binarySearchForZero(f, low, mid);
  }

  else if (result < 0) {
    return binarySearchForZero(f, mid, high);
  }

  return low;
}
