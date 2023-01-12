#ifndef STORY_HPP
#define STORY_HPP

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

class PageVar {
 public:
  // data field
  size_t page_num;
  std::string var_name;
  long int var_value;

  // method field
  // constructor
  PageVar();
  PageVar(size_t num, std::string name, long int value);

  //copy constructor
  PageVar(const PageVar & rhs);

  //assignment constructor
  PageVar & operator=(const PageVar & rhs);

  // Destructor
  ~PageVar();
};

class PageChoice {
 private:
  size_t this_page;
  size_t next_page;
  std::string text;
  // the newly added variable name_value pair
  std::pair<std::string, long int> name_val;
  int pair_flag;

 public:
  // constructor
  PageChoice();
  PageChoice(size_t curr, size_t next, std::string t, int flag);
  //copy constructor
  PageChoice(const PageChoice & rhs);
  //assignment constructor
  PageChoice & operator=(const PageChoice & rhs);
  // Destructor
  ~PageChoice();

  // make_pair
  void create_pair(std::string name, long int value);

  // get_pair
  std::pair<std::string, long int> get_pair() const;

  int get_flag() const;
  size_t get_next_page() const;
  std::string get_text() const;
};

class NewPage {
 private:
  size_t page_num;
  std::string page_type;
  std::string filename;
  std::vector<PageChoice> v_choice;
  // newly added for step 4
  std::vector<size_t> not_choice;

 public:
  // constructor
  NewPage(size_t num, std::string type, std::string file);
  //copy constructor
  NewPage(const NewPage & rhs);
  //assignment constructor
  NewPage & operator=(const NewPage & rhs);
  // Destructor
  ~NewPage();

  // add choice to the vector
  void add_choice(PageChoice choice);
  void set_not_choice(std::vector<size_t> not_valid);
  std::vector<size_t> get_not_choice() const;
  size_t get_num() const;
  std::string get_type() const;
  std::string get_file() const;
  std::vector<PageChoice> get_v_choice() const;
};

// override the print method
std::ostream & operator<<(std::ostream & s, const NewPage & rhs);

// define a function which checks whether the page number is a valid integer fits into size_t
size_t check_return_pagenum(std::string pagenum_str);

// define a function which checks whether the variable value is a valid long integer
long int check_var_value(std::string value_str);

// cyoa-step1 main
std::vector<NewPage> cyoa_step1(int argc, char ** argv);

// v_page error checking in step 2
void cyoa_step2(std::vector<NewPage> v_page);

// not_in function
int not_in(size_t num, std::vector<std::pair<size_t, size_t> > page_occur);

// not_in_vector function
int not_in_vector(size_t idx, std::vector<size_t> choice_idx);

// not_in_var function
int not_in_var(std::string name,
               std::vector<std::pair<std::string, long int> > name_value);

// get not_choice function
std::vector<size_t> get_invalid_choice(
    NewPage curr_page,
    std::vector<std::pair<std::string, long int> > name_value);

// reuse the check_return_pagenum function above the check whether a user input is a valid number or not
int str_digit(std::string user_input);

// get the v_page result with all error checking
std::vector<NewPage> cyoa_step12(int argc, char ** argv);

// find the page_choice of the page
std::vector<PageChoice> find_choice(size_t curr_page, std::vector<NewPage> v_page);

// find the page_type of the page
std::string find_type(size_t curr_page, std::vector<NewPage> v_page);

#endif
