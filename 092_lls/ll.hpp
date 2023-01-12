#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

class Tester;

class out_of_bound : public std::exception {
 public:
  const char * what() const throw() { return "The index is out of bound."; }
};

//YOUR CODE GOES HERE
template<typename T>
class LinkedList {
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;

    Node() : data(), next(NULL), prev(NULL) {}
    Node(T d, Node * n, Node * p) : data(d), next(n), prev(p) {}
  };

  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * curr = rhs.head;
    while (curr != NULL) {
      addBack(curr->data);
      curr = curr->next;
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      while (head != NULL) {
        Node * curr = head->next;
        delete head;
        head = curr;
      }

      Node * temp = rhs.head;
      while (temp != NULL) {
        addBack(temp->data);
        temp = temp->next;
      }

      size = rhs.size;
    }
    return *this;
  }

  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }

  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }

  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }

  bool remove(const T & item) {
    if (head->data == item) {
      head->next->prev = NULL;
      Node * temp = head->next;
      delete head;
      size--;
      head = temp;
      return true;
    }

    Node * curr = head;
    while (curr->next != NULL) {
      if (curr->data == item) {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        Node * temp = curr->next;
        delete curr;
        size--;
        curr = temp;
        return true;
      }
      curr = curr->next;
    }

    if (curr->data == item) {
      curr->prev->next = NULL;
      tail = curr->prev;
      delete curr;
      size--;
      return true;
    }

    return false;
  }

  T & operator[](int index) {
    try {
      if (index < 0 || index > size - 1) {
        throw out_of_bound();
      }
    }

    catch (out_of_bound & e) {
      std::cerr << e.what() << std::endl;
    }

    Node * curr = head;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    return curr->data;
  }

  const T & operator[](int index) const {
    try {
      if (index < 0 || index > size - 1) {
        throw out_of_bound();
      }
    }

    catch (out_of_bound & e) {
      std::cerr << e.what() << std::endl;
    }

    Node * curr = head;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    return curr->data;
  }

  int find(const T & item) const {
    Node * curr = head;
    int idx = 0;
    while (curr != NULL) {
      if (curr->data == item) {
        return idx;
      }
      curr = curr->next;
      idx++;
    }
    return -1;
  }

  int getSize() const { return size; }

  friend class Tester;
};

#endif
