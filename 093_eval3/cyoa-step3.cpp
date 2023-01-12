#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <climits>  // ULONG_MAX
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "story.hpp"

int main(int argc, char ** argv) {
  std::vector<NewPage> v_page = cyoa_step12(argc, argv);

  // use DFS to find cycle-free ways to win
  // declare useful containers
  std::stack<std::vector<std::pair<size_t, size_t> > > stack_path;
  std::vector<std::vector<std::pair<size_t, size_t> > > visited_path;
  std::vector<std::vector<std::pair<size_t, size_t> > > win_path;

  // push the first page node to the stack
  std::vector<std::pair<size_t, size_t> > curr_path;
  curr_path.push_back(std::make_pair(v_page[0].get_num(), 0));
  stack_path.push(curr_path);

  // continue pop out element when the stack_path is not empty
  while (!stack_path.empty()) {
    // get and pop the last in element in the stack
    curr_path = stack_path.top();
    stack_path.pop();
    std::vector<std::pair<size_t, size_t> > temp_path = curr_path;
    size_t curr_node = curr_path.back().first;

    // if the type is W, push the curr_path to the win_path
    if (find_type(curr_node, v_page) == "W") {
      win_path.push_back(curr_path);
    }

    // if the type is L, continue next loop
    if (find_type(curr_node, v_page) == "L") {
      continue;
    }

    // delete those tracking vectors which are in different path from the curr_path, make sure the visited path is not empty
    while ((visited_path.size() != 0) &&
           (visited_path.back().size() >= curr_path.size())) {
      visited_path.pop_back();
    }

    // use the last vector in the visited_path to track the visited pages or there is no element in the visited_path
    if ((visited_path.size() == 0) || (not_in(curr_node, visited_path.back()) == 1)) {
      // push the curr_path to the tracking vector
      visited_path.push_back(curr_path);
      // get all the next page choices for the curr_page
      std::vector<PageChoice> curr_choice = find_choice(curr_node, v_page);

      for (size_t i = 0; i < curr_choice.size(); i++) {
        // update the page choice
        curr_path.back().second = i + 1;
        // push the next page to the curr_path
        curr_path.push_back(std::make_pair(curr_choice[i].get_next_page(), 0));
        // push the updated curr_path to the stack
        stack_path.push(curr_path);
        // resume the curr_path for next loop
        curr_path = temp_path;
      }
    }
  }

  // print all cycle-free win_path
  // when there is no element in win_path
  if (win_path.size() == 0) {
    std::cout << "This story is unwinnable!\n";
  }

  // when the story is winnable
  for (size_t i = 0; i < win_path.size(); i++) {
    for (size_t j = 0; j < win_path[i].size(); j++) {
      if (win_path[i][j].second == 0) {
        std::cout << win_path[i][j].first << "("
                  << "win"
                  << ")";
      }
      else {
        std::cout << win_path[i][j].first << "(" << win_path[i][j].second << ")"
                  << ",";
      }
    }
    std::cout << std::endl;
  }

  return EXIT_SUCCESS;
}
