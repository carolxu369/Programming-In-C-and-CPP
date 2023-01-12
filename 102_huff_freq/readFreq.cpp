#include "readFreq.h"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  std::ifstream f;
  f.open(fname);
  if (!f.is_open()) {
    std::cerr << "Could not open file";
    exit(EXIT_FAILURE);
  }

  uint64_t * frequency = new uint64_t[257]();
  int curr_char;
  while ((curr_char = f.get()) != EOF) {
    frequency[curr_char]++;
  }
  frequency[256] = 1;
  f.close();
  return frequency;
}
