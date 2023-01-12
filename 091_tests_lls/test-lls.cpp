#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME

    IntList il;
    il.addFront(1);
    assert(il.head != NULL && il.head->data == 1 && il.head->prev == NULL &&
           il.head->next == NULL);
    assert(il.tail != NULL && il.tail == il.head);
    assert(il.getSize() == 1);
    assert(il[0] == 1);

    il.addFront(2);
    assert(il.head != NULL && il.head->prev == NULL && il.head == il.head->next->prev &&
           il.head->next->next == NULL);
    assert(il.tail != NULL && il.tail == il.head->next);
    assert(il.getSize() == 2);
    assert(il[0] == 2 && il[1] == 1);
  }

  void testAddBack() {
    IntList il;
    il.addBack(1);
    assert(il.head != NULL && il.head->data == 1 && il.head->prev == NULL &&
           il.head->next == NULL);
    assert(il.tail != NULL && il.tail == il.head);
    assert(il.getSize() == 1);
    assert(il[0] == 1);

    il.addBack(2);
    assert(il.head != NULL && il.head->prev == NULL && il.head == il.head->next->prev &&
           il.head->next->next == NULL);
    assert(il.tail != NULL && il.tail == il.head->next);
    assert(il.getSize() == 2);
    assert(il[0] == 1 && il[1] == 2);
  }

  void testCopyCtor() {
    IntList il_orig;
    il_orig.addFront(1);
    il_orig.addFront(2);

    IntList il(il_orig);
    assert(il.head != NULL && il.head->prev == NULL && il.head == il.head->next->prev &&
           il.head->next->next == NULL);
    assert(il.tail != NULL && il.tail == il.head->next);
    assert(il_orig.head != il.head);
    assert(il.getSize() == 2);
    assert(il[0] == 2 && il[1] == 1);
  }

  void testAssign() {
    IntList il_orig;
    il_orig.addFront(1);
    il_orig.addFront(2);

    IntList il;
    il = il_orig;
    assert(il.head != NULL && il.head->prev == NULL && il.head == il.head->next->prev &&
           il.head->next->next == NULL);
    assert(il.tail != NULL && il.tail == il.head->next);
    assert(il_orig.head != il.head);
    assert(il.getSize() == 2);
    assert(il[0] == 2 && il[1] == 1);

    IntList il_1;
    il_1.addFront(3);
    il_1.addFront(4);

    il_1 = il;
    assert(il_1.head != NULL && il_1.head->prev == NULL &&
           il_1.head == il_1.head->next->prev && il_1.head->next->next == NULL);
    assert(il_1.tail != NULL && il_1.tail == il_1.head->next);
    assert(il.head != il_1.head);
    assert(il_1.getSize() == 2);
    assert(il_1[0] == 2 && il_1[1] == 1);
  }

  void testRemove() {
    IntList il;
    il.addFront(1);
    il.addFront(2);
    il.addFront(3);
    il.addFront(3);
    il.addFront(4);

    assert(il[0] == 4 && il[1] == 3 && il[2] == 3 && il[3] == 2 && il[4] == 1);
    assert(il.getSize() == 5);
    assert(il.remove(3) == true);
    assert(il.getSize() == 4);
    assert(il.find(1) == 3);
    assert(il.find(2) == 2);
    assert(il.find(3) == 1);
    assert(il.find(4) == 0);
    assert(il[0] == 4 && il[1] == 3 && il[2] == 2 && il[3] == 1);
    assert(il.head->data == 4);
    assert(il.tail->data == 1);
    assert(il.head->next->data == 3);
    assert(il.head->next->prev->data == 4);
    assert(il.head->next->next->data == 2);
    assert(il.head->next->next->prev->data == 3);

    assert(il.remove(3) == true);
    assert(il.getSize() == 3);
    assert(il[0] == 4 && il[1] == 2 && il[2] == 1);
    assert(il.head->data == 4);
    assert(il.tail->data == 1);
    assert(il.head->next->data == 2);
    assert(il.head->next->prev->data == 4);

    assert(il.remove(3) == false);
    assert(il.remove(5) == false);

    assert(il.remove(1) == true);
    assert(il.getSize() == 2);
    assert(il[0] == 4 && il[1] == 2);
    assert(il.head->data == 4);
    assert(il.tail->data == 2);
    assert(il.head->next->data == 2);
    assert(il.head->next->prev->data == 4);

    IntList il_1;
    il_1.addFront(1);
    il_1.addFront(2);

    il_1.remove(2);
    assert(il_1.getSize() == 1);
    assert(il_1.head->data == 1 && il_1.head->next == NULL && il_1.head->prev == NULL);
    assert(il_1.tail != NULL && il_1.head == il_1.tail);

    IntList il_2;
    il_2.addFront(1);
    il_2.addFront(2);

    il_2.remove(2);
    il_2.remove(1);
    assert(il_2.getSize() == 0);
    assert(il_2.head == NULL);
    assert(il_2.tail == NULL);

    IntList il_3;
    il_3.addBack(1);
    il_3.addBack(2);
    il_3.addBack(2);
    il_3.addBack(3);

    assert(il_3[0] == 1 && il_3[1] == 2 && il_3[2] == 2 && il_3[3] == 3);
    assert(il_3.getSize() == 4);
    assert(il_3.remove(2) == true);
    assert(il_3.getSize() == 3);
    assert(il_3[0] == 1 && il_3[1] == 2 && il_3[2] == 3);
    assert(il_3.head->data == 1);
    assert(il_3.tail->data == 3);
    assert(il_3.head->next->data == 2);
    assert(il_3.head->next->prev->data == 1);
    assert(il_3.head->next->next->data == 3);
    assert(il_3.head->next->next->prev->data == 2);
  }

  // many more tester methods
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testCopyCtor();
  t.testAssign();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
