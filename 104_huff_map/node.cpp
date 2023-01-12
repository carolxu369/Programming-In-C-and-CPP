#include "node.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  if (sym != NO_SYM) {
    theMap[sym] = b;
  }
  else {
    left->buildMap(b.plusZero(), theMap);
    right->buildMap(b.plusOne(), theMap);
  }
}
