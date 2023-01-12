#include "story.hpp"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <climits>  // ULONG_MAX
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// class PageVar
// constructor
PageVar::PageVar() {
}
PageVar::PageVar(size_t num, std::string name, long int value) :
    page_num(num), var_name(name), var_value(value) {
}

//copy constructor
PageVar::PageVar(const PageVar & rhs) :
    page_num(rhs.page_num), var_name(rhs.var_name), var_value(rhs.var_value) {
}

//assignment constructor
PageVar & PageVar::operator=(const PageVar & rhs) {
  if (this != &rhs) {
    page_num = rhs.page_num;
    var_name = rhs.var_name;
    var_value = rhs.var_value;
  }
  return *this;
}

// Destructor
PageVar::~PageVar() {
}

// class PageChoice
// constructor
PageChoice::PageChoice() {
}
PageChoice::PageChoice(size_t curr, size_t next, std::string t, int flag) :
    this_page(curr), next_page(next), text(t), name_val(), pair_flag(flag) {
}

//copy constructor
PageChoice::PageChoice(const PageChoice & rhs) :
    this_page(rhs.this_page),
    next_page(rhs.next_page),
    text(rhs.text),
    name_val(rhs.name_val),
    pair_flag(rhs.pair_flag) {
}

//assignment constructor
PageChoice & PageChoice::operator=(const PageChoice & rhs) {
  if (this != &rhs) {
    this_page = rhs.this_page;
    next_page = rhs.next_page;
    text = rhs.text;
    name_val = rhs.name_val;
    pair_flag = rhs.pair_flag;
  }
  return *this;
}

// Destructor
PageChoice::~PageChoice() {
}

// make_pair
void PageChoice::create_pair(std::string name, long int value) {
  name_val = std::make_pair(name, value);
  pair_flag = 1;
}

// get_pair
std::pair<std::string, long int> PageChoice::get_pair() const {
  return name_val;
}

int PageChoice::get_flag() const {
  return pair_flag;
}

size_t PageChoice::get_next_page() const {
  return next_page;
}

std::string PageChoice::get_text() const {
  return text;
}

//class NewPage
// constructor
NewPage::NewPage(size_t num, std::string type, std::string file) :
    page_num(num), page_type(type), filename(file), v_choice(), not_choice() {
}

//copy constructor
NewPage::NewPage(const NewPage & rhs) :
    page_num(rhs.page_num),
    page_type(rhs.page_type),
    filename(rhs.filename),
    v_choice(rhs.v_choice),
    not_choice(rhs.not_choice) {
}

//assignment constructor
NewPage & NewPage::operator=(const NewPage & rhs) {
  if (this != &rhs) {
    page_num = rhs.page_num;
    page_type = rhs.page_type;
    filename = rhs.filename;
    v_choice = rhs.v_choice;
    not_choice = rhs.not_choice;
  }
  return *this;
}

// Destructor
NewPage::~NewPage() {
}

// add choice to the vector
void NewPage::add_choice(PageChoice choice) {
  v_choice.push_back(choice);
}

void NewPage::set_not_choice(std::vector<size_t> not_valid) {
  not_choice = not_valid;
}

std::vector<size_t> NewPage::get_not_choice() const {
  return not_choice;
}

size_t NewPage::get_num() const {
  return page_num;
}

std::string NewPage::get_type() const {
  return page_type;
}

std::string NewPage::get_file() const {
  return filename;
}

std::vector<PageChoice> NewPage::get_v_choice() const {
  return v_choice;
}

// override the print method
std::ostream & operator<<(std::ostream & s, const NewPage & rhs) {
  // check whether can open the page file
  std::ifstream file;
  file.open(rhs.get_file().c_str());
  // close file
  if (!file.is_open()) {
    std::cerr << "Could not open the file.\n";
    exit(EXIT_FAILURE);
  }
  std::string curr_line;
  // print text of the file
  while (!file.eof()) {
    std::getline(file, curr_line);
    s << curr_line << std::endl;
  }

  if (rhs.get_type() == "N") {
    std::vector<size_t> not_choice = rhs.get_not_choice();
    // s << "   " << std::endl;
    s << "What would you like to do?" << std::endl;
    s << "   " << std::endl;

    for (size_t i = 0; i < rhs.get_v_choice().size(); i++) {
      if (not_in_vector(i + 1, not_choice) == 1) {
        s << " " << i + 1 << "."
          << " " << rhs.get_v_choice()[i].get_text() << std::endl;
      }
      else {
        s << " " << i + 1 << "."
          << " "
          << "<UNAVAILABLE>" << std::endl;
      }
    }
  }

  else if (rhs.get_type() == "W") {
    //s << "   " << std::endl;
    s << "Congratulations! You have won. Hooray!" << std::endl;
  }

  else if (rhs.get_type() == "L") {
    //s << "   " << std::endl;
    s << "Sorry, you have lost. Better luck next time!" << std::endl;
  }

  file.close();

  return s;
}

// not_in_vector function
int not_in_vector(size_t idx, std::vector<size_t> choice_idx) {
  int result = 1;

  for (size_t i = 0; i < choice_idx.size(); i++) {
    if (idx == choice_idx[i]) {
      result = 0;
      break;
    }
  }

  return result;
}

// not_in_var function
int not_in_var(std::string name,
               std::vector<std::pair<std::string, long int> > name_value) {
  int result = 1;

  for (size_t i = 0; i < name_value.size(); i++) {
    if (name == name_value[i].first) {
      result = 0;
      break;
    }
  }

  return result;
}

// get not_choice function
std::vector<size_t> get_invalid_choice(
    NewPage curr_page,
    std::vector<std::pair<std::string, long int> > name_value) {
  std::vector<size_t> result;
  std::vector<PageChoice> curr_choice = curr_page.get_v_choice();

  for (size_t i = 0; i < curr_choice.size(); i++) {
    if (curr_choice[i].get_flag() != 1) {
      continue;
    }
    else {
      std::pair<std::string, long int> curr_pair = curr_choice[i].get_pair();
      if (not_in_var(curr_pair.first, name_value) == 1) {
        if (curr_pair.second == 0) {
          continue;
        }
        else {
          result.push_back(i + 1);
        }
      }
      else {
        for (size_t k = 0; k < name_value.size(); k++) {
          if (name_value[k].first == curr_pair.first) {
            if (name_value[k].second == curr_pair.second) {
              break;
            }
            else {
              result.push_back(i + 1);
              break;
            }
          }
        }
      }
    }
  }
  return result;
}

// define a function which checks whether the page number is a valid integer fits into size_t
size_t check_return_pagenum(std::string pagenum_str) {
  size_t num_it = 0;

  for (size_t i = 0; i < pagenum_str.length(); i++) {
    if (isdigit(pagenum_str[i]) != 0) {
      num_it = i;
      break;
    }
  }

  for (size_t i = num_it; i < pagenum_str.length(); i++) {
    if (isdigit(pagenum_str[i]) == 0) {
      std::cerr << "The page number is not a valid integer fits into size_t.\n";
      exit(EXIT_FAILURE);
    }
  }

  size_t page_num = strtoul(pagenum_str.c_str(), NULL, 10);
  // delete page_num_str.c_str(), not sure whether this need to delete

  return page_num;
}

// define a function which checks whether the variable value is a valid long integer
long int check_var_value(std::string value_str) {
  size_t num_it = 0;

  for (size_t i = 0; i < value_str.length(); i++) {
    if (isdigit(value_str[i]) != 0) {
      num_it = i;
      break;
    }
  }

  for (size_t i = num_it; i < value_str.length(); i++) {
    if (isdigit(value_str[i]) == 0) {
      std::cerr << "The variable value is not a valid long integer.\n";
      exit(EXIT_FAILURE);
    }
  }

  long int var_value = strtol(value_str.c_str(), NULL, 10);
  // delete page_num_str.c_str(), not sure whether this need to delete

  return var_value;
}

std::vector<NewPage> cyoa_step1(int argc, char ** argv) {
  // first check whether the user enter the directory correctly
  if (argc != 2) {
    std::cerr << "You enter the wrong number of directory.\n";
    exit(EXIT_FAILURE);
  }

  // open the story.txt in this directory and check whether can open this file successfully
  std::stringstream strstream;
  std::string f_name;
  std::string dir = argv[1];
  strstream << dir << "/story.txt";
  f_name = strstream.str();
  std::ifstream f_story;
  f_story.open(f_name.c_str());
  // close f_story
  if (!f_story.is_open()) {
    std::cerr << "Could not open the file.\n";
    exit(EXIT_FAILURE);
  }

  // declare a vector to store page number
  //std::vector<std::pair<size_t, std::string> > num_type;
  std::vector<size_t> v_num;
  // create a vector to store all NewPage objects
  std::vector<NewPage> v_page;
  std::string curr_line;

  while (!f_story.eof()) {
    // get the current line of the story.txt and skip if current line is a blank line
    std::getline(f_story, curr_line);

    // new page case
    if (curr_line.find('@') != std::string::npos) {
      size_t at = curr_line.find('@');
      std::string page_num_str = curr_line.substr(0, at);
      std::string page_type = curr_line.substr(at + 1, 1);
      std::string page_file = curr_line.substr(at + 3, curr_line.length() - (at + 3));

      // check whether the page number is a valid integer fits into size_t
      size_t page_num = check_return_pagenum(page_num_str);

      // add the new page number to v_num and check whether the page delcaration is in order or not
      if (v_num.size() == 0) {
        v_num.push_back(page_num);
      }
      else {
        std::vector<size_t>::iterator it = v_num.begin();
        while (it != v_num.end()) {
          if (*it >= page_num) {
            std::cerr << "Page declaration not in order or has already been declared.\n";
            exit(EXIT_FAILURE);
          }
          ++it;
        }
        v_num.push_back(page_num);
      }

      // check whether the page_type is a valid type
      if ((page_type != "W") && (page_type != "L") && (page_type != "N")) {
        std::cerr << "Page type is not valid.\n";
        exit(EXIT_FAILURE);
      }

      // add the directory to the page_file name
      std::stringstream curr_sstr;
      curr_sstr << dir << "/" << page_file;
      page_file = curr_sstr.str();

      // create a NewPage object
      NewPage new_page(page_num, page_type, page_file);
      v_page.push_back(new_page);
    }

    // page choice case
    else if ((curr_line.find('@') == std::string::npos) &&
             (curr_line.find(':') != std::string::npos)) {
      size_t slice_1 = curr_line.find(':');
      size_t slice_2 = curr_line.find(':', slice_1 + 1);

      std::string curr_page = curr_line.substr(0, slice_1);
      std::string next_page = curr_line.substr(slice_1 + 1, slice_2 - (slice_1 + 1));
      std::string choice_text =
          curr_line.substr(slice_2 + 1, curr_line.length() - (slice_2 + 1));

      // check whether the page number is valid
      size_t curr_page_num = check_return_pagenum(curr_page);
      size_t next_page_num = check_return_pagenum(next_page);

      // check whether the page declaration has happened before
      int dec_flag = 0;
      for (size_t i = 0; i < v_num.size(); i++) {
        if (v_num[i] == curr_page_num) {
          dec_flag = 1;
          break;
        }
      }
      if (dec_flag == 0) {
        std::cerr << "Page has not declared.\n";
        exit(EXIT_FAILURE);
      }

      // create a PageChoice object and add to NewPage object
      PageChoice page_choice(curr_page_num, next_page_num, choice_text, 0);

      std::vector<NewPage>::iterator it = v_page.begin();
      while (it != v_page.end()) {
        if ((*it).get_num() == curr_page_num) {
          // check whether it's a win or lose page
          if (((*it).get_type() == "W") || ((*it).get_type() == "L")) {
            std::cerr << "Win and Lose pages must not have any choices.\n";
            exit(EXIT_FAILURE);
          }

          (*it).add_choice(page_choice);
        }
        ++it;
      }
    }
  }
  f_story.close();

  return v_page;
}

// not_in function
int not_in(size_t num, std::vector<std::pair<size_t, size_t> > page_occur) {
  int result = 1;

  for (size_t i = 0; i < page_occur.size(); i++) {
    if (num == page_occur[i].first) {
      result = 0;
      break;
    }
  }

  return result;
}

// reuse the check_return_pagenum function above the check whether a user input is a valid number or not
int str_digit(std::string user_input) {
  size_t num_it = 0;
  int digit_flag = 0;

  for (size_t i = 0; i < user_input.length(); i++) {
    if (isdigit(user_input[i]) != 0) {
      num_it = i;
      break;
    }
  }

  for (size_t i = num_it; i < user_input.length(); i++) {
    if (isdigit(user_input[i]) == 0) {
      digit_flag = 1;
      break;
    }
  }

  return digit_flag;
}

// v_page error checking in step 2
void cyoa_step2(std::vector<NewPage> v_page) {
  std::vector<std::pair<size_t, size_t> > page_occur;

  // construct the page_occur vector with page_num and the number of occurence of that page
  for (size_t i = 0; i < v_page.size(); i++) {
    page_occur.push_back(std::make_pair(v_page[i].get_num(), 0));
  }

  // check whether every page that is referenced by a choice is valid
  for (size_t i = 0; i < v_page.size(); i++) {
    for (size_t j = 0; j < v_page[i].get_v_choice().size(); j++) {
      if (not_in(v_page[i].get_v_choice()[j].get_next_page(), page_occur) == 1) {
        std::cerr << "Exist page referenced by a choice is not valid.\n";
        exit(EXIT_FAILURE);
      }
    }
  }

  int win_page = 0;
  int lose_page = 0;

  // update the number of reference for each page
  // update the number of win and lose page in the story
  for (size_t i = 0; i < v_page.size(); i++) {
    if (v_page[i].get_type() == "W") {
      win_page = 1;
    }

    if (v_page[i].get_type() == "L") {
      lose_page = 1;
    }

    for (size_t j = 0; j < v_page[i].get_v_choice().size(); j++) {
      size_t refer_page = v_page[i].get_v_choice()[j].get_next_page();
      for (size_t k = 0; k < page_occur.size(); k++) {
        if (refer_page == page_occur[k].first) {
          page_occur[k].second++;
        }
      }
    }
  }

  // check whether every page is referenced by at least one other page's choice
  for (size_t i = 0; i < page_occur.size(); i++) {
    if ((page_occur[i].first != 0) && (page_occur[i].second < 1)) {
      std::cerr << "Exist a page is not referenced by other pages.\n";
      exit(EXIT_FAILURE);
    }
  }

  // check whether the story has at least one win page and one lose page
  if (win_page == 0) {
    std::cerr << "The story doesn't have a win page.\n";
    exit(EXIT_FAILURE);
  }

  if (lose_page == 0) {
    std::cerr << "The story doesn't have a lose page.\n";
    exit(EXIT_FAILURE);
  }
}

// get the v_page result with all error checking
std::vector<NewPage> cyoa_step12(int argc, char ** argv) {
  std::vector<NewPage> v_page = cyoa_step1(argc, argv);

  std::vector<std::pair<size_t, size_t> > page_occur;

  // construct the page_occur vector with page_num and the number of occurence of that page
  for (size_t i = 0; i < v_page.size(); i++) {
    page_occur.push_back(std::make_pair(v_page[i].get_num(), 0));
  }

  // check whether every page that is referenced by a choice is valid
  for (size_t i = 0; i < v_page.size(); i++) {
    for (size_t j = 0; j < v_page[i].get_v_choice().size(); j++) {
      if (not_in(v_page[i].get_v_choice()[j].get_next_page(), page_occur) == 1) {
        std::cerr << "Exist page referenced by a choice is not valid.\n";
        exit(EXIT_FAILURE);
      }
    }
  }

  int win_page = 0;
  int lose_page = 0;

  // update the number of reference for each page
  // update the number of win and lose page in the story
  for (size_t i = 0; i < v_page.size(); i++) {
    if (v_page[i].get_type() == "W") {
      win_page = 1;
    }

    if (v_page[i].get_type() == "L") {
      lose_page = 1;
    }

    for (size_t j = 0; j < v_page[i].get_v_choice().size(); j++) {
      size_t refer_page = v_page[i].get_v_choice()[j].get_next_page();
      for (size_t k = 0; k < page_occur.size(); k++) {
        if (refer_page == page_occur[k].first) {
          page_occur[k].second++;
        }
      }
    }
  }

  // check whether every page is referenced by at least one other page's choice
  for (size_t i = 0; i < page_occur.size(); i++) {
    if ((page_occur[i].first != 0) && (page_occur[i].second < 1)) {
      std::cerr << "Exist a page is not referenced by other pages.\n";
      exit(EXIT_FAILURE);
    }
  }

  // check whether the story has at least one win page and one lose page
  if (win_page == 0) {
    std::cerr << "The story doesn't have a win page.\n";
    exit(EXIT_FAILURE);
  }

  if (lose_page == 0) {
    std::cerr << "The story doesn't have a lose page.\n";
    exit(EXIT_FAILURE);
  }

  return v_page;
}

// find the page_choice of the page
std::vector<PageChoice> find_choice(size_t curr_page, std::vector<NewPage> v_page) {
  std::vector<PageChoice> result;
  for (size_t i = 0; i < v_page.size(); i++) {
    if (curr_page == v_page[i].get_num()) {
      result = v_page[i].get_v_choice();
      return result;
    }
  }
  return result;
}

// find the page_type of the page
std::string find_type(size_t curr_page, std::vector<NewPage> v_page) {
  std::string result;
  for (size_t i = 0; i < v_page.size(); i++) {
    if (curr_page == v_page[i].get_num()) {
      result = v_page[i].get_type();
      return result;
    }
  }
  return result;
}
