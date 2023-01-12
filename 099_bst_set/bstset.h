#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 private:
  class Node {
   public:
    T key;
    Node * left;
    Node * right;
    // constructor
    Node() : key(0), left(NULL), right(NULL) {}
    Node(T k) : key(k), left(NULL), right(NULL) {}
  };

  Node * root;

 public:
  // constructor
  BstSet<T>() : root(NULL) {}

  // copy constructor
  BstSet(const BstSet & rhs) : root(NULL) { root = constructor(rhs.root); }

  Node * constructor(Node * curr_node) {
    if (curr_node == NULL) {
      return NULL;
    }
    Node * new_node = new Node(curr_node->key);
    new_node->left = constructor(curr_node->left);
    new_node->right = constructor(curr_node->right);
    return new_node;
  }

  // assignment constructor
  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      destructor(root);
      root = constructor(rhs.root);
    }
    return *this;
  }

  // add
  virtual void add(const T & key) {
    Node ** curr_node = &root;
    while (*curr_node != NULL) {
      if ((*curr_node)->key == key) {
        return;
      }
      else if ((*curr_node)->key > key) {
        curr_node = &(*curr_node)->left;
      }
      else if ((*curr_node)->key < key) {
        curr_node = &(*curr_node)->right;
      }
    }
    *curr_node = new Node(key);
  }

  // lookup
  virtual bool contains(const T & key) const {
    Node * curr_node = root;
    while (curr_node != NULL) {
      if (curr_node->key == key) {
        return true;
      }
      else if (curr_node->key > key) {
        curr_node = curr_node->left;
      }
      else if (curr_node->key < key) {
        curr_node = curr_node->right;
      }
    }

    return false;
  }

  // remove
  virtual void remove(const T & key) {
    Node ** curr_node = &root;
    Node * temp = NULL;

    while (*curr_node != NULL) {
      if ((*curr_node)->key == key) {
        if ((*curr_node)->left == NULL) {
          temp = (*curr_node)->right;
          delete *curr_node;
          *curr_node = temp;
        }

        else if ((*curr_node)->right == NULL) {
          temp = (*curr_node)->left;
          delete *curr_node;
          *curr_node = temp;
        }

        else {
          Node ** new_node = curr_node;
          curr_node = &(*curr_node)->left;
          while ((*curr_node)->right != NULL) {
            curr_node = &(*curr_node)->right;
          }

          (*new_node)->key = (*curr_node)->key;
          temp = (*curr_node)->left;
          delete (*curr_node);
          *curr_node = temp;
        }
      }

      else if ((*curr_node)->key > key) {
        curr_node = &(*curr_node)->left;
      }
      else {
        curr_node = &(*curr_node)->right;
      }
    }
  }
  //virtual ~Map<K,V>() {}

  void destructor(Node * curr_node) {
    if (curr_node != NULL) {
      destructor(curr_node->left);
      destructor(curr_node->right);
      delete curr_node;
    }
  }

  ~BstSet<T>() { destructor(root); }
};
