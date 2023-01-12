//#ifndef __INT_MATRIX_H___
//#define __INT_MATRIX_H___
//#include "IntMatrix.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

void print_line(std::vector<std::string> lines) {
  std::vector<std::string>::iterator it = lines.begin();
  while (it != lines.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::string curr_line;
    std::vector<std::string> lines;

    while (!std::cin.eof()) {
      if (!std::cin.good()) {
        std::cerr << "Could not open std::cin";
      }
      std::getline(std::cin, curr_line);
      lines.push_back(curr_line);
    }

    std::sort(lines.begin(), lines.end());

    print_line(lines);

    lines.clear();
  }

  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream f;
      f.open(argv[i]);
      if (!f.is_open()) {
        //std::ifstream f(argv[i]);
        //if (f.fail()) {
        std::cerr << "Could not open file";
        return EXIT_FAILURE;
      }
      std::string curr_line;
      std::vector<std::string> lines;

      while (!f.eof()) {
        std::getline(f, curr_line);
        lines.push_back(curr_line);
      }

      std::sort(lines.begin(), lines.end());

      print_line(lines);

      lines.clear();

      f.close();
    }
  }
  return EXIT_SUCCESS;
}
