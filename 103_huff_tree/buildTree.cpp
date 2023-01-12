#include <stdio.h>

#include <cstdlib>
#include <fstream>

#include "node.h"

Node * buildTree(uint64_t * counts) {
  priority_queue_t pq;

  for (size_t i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }

  if (pq.empty()) {
    return NULL;
  }

  while (pq.size() != 1) {
    Node * left = pq.top();
    pq.pop();
    Node * right = pq.top();
    pq.pop();
    Node * new_node = new Node(left, right);
    pq.push(new_node);
  }
  return pq.top();
}
