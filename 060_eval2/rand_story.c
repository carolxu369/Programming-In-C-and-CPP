#include "rand_story.h"

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// use the header files from eval 1

// this function return a catarray_t given a file with categories and words
catarray_t * get_catarray_t(FILE * f) {
  // declare the array of all categories
  catarray_t * cat_array = malloc(sizeof(*cat_array));
  // free cat_array;
  cat_array->arr = malloc(sizeof(*cat_array->arr));
  // free cat_array->arr;
  cat_array->n = 0;

  // use getline to operate on each line of the file
  size_t sz = 0;
  char * line = NULL;
  // declare a string cat_name to store the category name and a string curr_word to store the word of that category
  char * cat_name = NULL;
  char * curr_word = NULL;

  while (getline(&line, &sz, f) >= 0) {
    size_t len = strlen(line);

    // first check whether each line of the file has least one :
    int flag = 0;
    for (size_t i = 0; i < len; i++) {
      if (line[i] == ':') {
        flag = 1;
      }
    }
    if (flag == 0) {
      perror("One line doesn't have ':' to separate category name and word.\n");
      exit(EXIT_FAILURE);
    }

    char * ptr = line;

    // get the category name from the line
    // declare a cat_count to count the number of character being added to the cat_name
    size_t cat_count = 1;
    cat_name = realloc(cat_name, cat_count * sizeof(*cat_name));
    // first copy an empty string to the cat_name in case the cat_name is an empty string
    char * empty_str = "";
    strcpy(cat_name, empty_str);

    // loop through the line until finding ':'
    while (*ptr != ':') {
      // increase the character count in the cat_name and realloc the size of cat_name
      cat_count++;
      cat_name = realloc(cat_name, cat_count * sizeof(*cat_name));
      // convert the single character to string to do the following strcat to append the character to the cat_name
      char curr_str[2] = {*ptr, '\0'};
      strcat(cat_name, curr_str);
      ptr++;
      // free cat_name;
    }

    // move the pointer to the starting position of the word
    ptr++;

    // first set curr_word as an empty string
    size_t word_count = 1;
    curr_word = realloc(curr_word, word_count * sizeof(*curr_word));
    strcpy(curr_word, empty_str);

    // loop through the line until finding '\n'
    while (*ptr != '\n') {
      // append the new character to the curr_word string
      word_count++;
      curr_word = realloc(curr_word, word_count * sizeof(*curr_word));
      char curr_str[2] = {*ptr, '\0'};
      strcat(curr_word, curr_str);
      ptr++;
      // free curr_word;
    }

    // check whether the cat_name has already been included in the cat_array
    int cat_occur = 0;
    for (size_t i = 0; i < cat_array->n; i++) {
      if (strcmp(cat_name, cat_array->arr[i].name) == 0) {
        cat_occur = 1;
      }
    }

    // if the cat_name is in the cat_array, then append the curr_word to this cat_name word list and increment n_words by 1
    if (cat_occur == 1) {
      for (size_t i = 0; i < cat_array->n; i++) {
        if (strcmp(cat_name, cat_array->arr[i].name) == 0) {
          cat_array->arr[i].n_words++;
          cat_array->arr[i].words =
              realloc(cat_array->arr[i].words,
                      cat_array->arr[i].n_words * sizeof(*cat_array->arr[i].words));
          // free cat_array->arr[i]->words
          cat_array->arr[i].words[cat_array->arr[i].n_words - 1] = strdup(curr_word);
          // free cat_array->arr[i]->words[n_words-1]
          break;
        }
      }
    }
    else {
      // if cat_array is empty or no cat_names in cat_array match the new cat_name
      // create a new category_t for this new cat_name and add that to the cat_array
      category_t * new_cat = malloc(sizeof(*new_cat));
      // free new_cat
      new_cat->name = strdup(cat_name);
      // free new_cat->name
      new_cat->n_words = 1;
      new_cat->words = malloc(1 * sizeof(*new_cat->words));
      // free new_cat->words
      // new_cat->words[n_words-1] = malloc(len_word*sizeof(*new_cat->words[n_words-1]));
      new_cat->words[0] = strdup(curr_word);
      // free new_cat->words[n_words-1]

      // add this new category_t to cat_array
      cat_array->n++;
      cat_array->arr = realloc(cat_array->arr, cat_array->n * sizeof(*cat_array->arr));
      // free cat_array->arr
      cat_array->arr[cat_array->n - 1] = *new_cat;
      free(new_cat);
    }
  }

  // free part
  free(line);
  free(cat_name);
  free(curr_word);

  return cat_array;
}

// this function free all the memory used by catarray_t
void free_catarray_t(catarray_t * cat_array) {
  for (size_t i = 0; i < cat_array->n; i++) {
    for (size_t j = 0; j < cat_array->arr[i].n_words; j++) {
      free(cat_array->arr[i].words[j]);
    }
    free(cat_array->arr[i].words);
    free(cat_array->arr[i].name);
  }
  free(cat_array->arr);
  free(cat_array);
}

// this function free all the memory used by category_t without name
void free_category_t(category_t * cat_word) {
  for (size_t i = 0; i < cat_word->n_words; i++) {
    free(cat_word->words[i]);
  }
  free(cat_word->words);
  //free(cat_word->name);
  free(cat_word);
}

// this function take two files as arguments and print out the story line with backreference or words replacement (exactly step 3)
void print_story(FILE * f_word, FILE * f_story) {
  // first get the cat_array from story-step 2
  catarray_t * cat_array = get_catarray_t(f_word);
  // free cat_array

  // declare a category_t to store backreference words
  category_t * back_words = malloc(sizeof(*back_words));
  // free back_words
  back_words->n_words = 0;
  back_words->words = malloc(back_words->n_words * sizeof(*back_words->words));
  // free back_words->words

  // now replace the blanks in story with words
  // use getline to operate on each line of the file
  size_t sz = 0;
  char * line = NULL;
  while (getline(&line, &sz, f_story) >= 0) {
    size_t len = strlen(line);

    // first check whether the number of underscores is enough to make valid blanks
    int _count = 0;
    for (size_t i = 0; i < len; i++) {
      if (line[i] == '_') {
        _count++;
      }
    }
    if ((_count % 2) != 0) {
      perror("Some blanks begin but not end with matching underscores.\n");
      exit(EXIT_FAILURE);
    }

    // print each character in the line with blanks replaced
    char * ptr = line;
    while (*ptr != '\0') {
      // if find a starting underscore, declare an empty string using realloc to store the category name until meeting the closing underscore
      if (*ptr == '_') {
        char * cat_name = NULL;
        // declare a count to record the size change of the cat_name
        size_t count = 1;
        cat_name = realloc(cat_name, count * sizeof(*cat_name));
        // first concatenate the cat_name with an empty string in the case if the starting underscore and closing underscore are adjacent
        // get this idea of strcpy and strcat from MLP 057
        char * empty_cat = "";
        strcpy(cat_name, empty_cat);
        ptr++;
        // use another loop to find the closing underscore
        while (*ptr != '_') {
          // increase the cat_name size to store the new character
          count++;
          cat_name = realloc(cat_name, count * sizeof(*cat_name));
          // convert the single character to string to do the following strcat
          // to add the character to the cat_name
          char curr_str[2] = {*ptr, '\0'};
          strcat(cat_name, curr_str);
          ptr++;
        }

        // first check whether cat_name is a valid integer of at least one
        int flag = 0;
        char * cat_int = NULL;
        size_t int_count = 1;
        cat_int = realloc(cat_int, int_count * sizeof(*cat_int));
        // free cat_int
        strcpy(cat_int, empty_cat);
        char * cat_ptr = cat_name;

        // jump all the spaces before any possible digit
        // once find the digit break the loop
        while (*cat_ptr != '\0') {
          if ((*cat_ptr == ' ') | (*cat_ptr == '\t')) {
            cat_ptr++;
            continue;
          }
          else {
            break;
          }
        }

        // the pointer is pointing at the possible first digit
        // loop to find continuous digit and add new digit to cat_int
        // once encounter a character that is not a digit, change cat_int back to an empty string
        // and break the loop
        while (*cat_ptr != '\0') {
          if (isdigit(*cat_ptr) != 0) {
            int_count++;
            cat_int = realloc(cat_int, int_count * sizeof(*cat_int));
            char curr_int[2] = {*cat_ptr, '\0'};
            strcat(cat_int, curr_int);
            cat_ptr++;
          }
          else {
            cat_int = realloc(cat_int, 1 * sizeof(*cat_int));
            strcpy(cat_int, empty_cat);
            break;
          }
        }

        // check whether there are digits in cat_int
        // if cat_int contains digit, do backreference to find the replacement word
        if (strlen(cat_int) > 0) {
          size_t back_int = atoi(cat_int);
          // make sure the integer is at least of one
          if (back_int >= 1) {
            if (back_int > back_words->n_words) {
              perror("The backreference word list is not enough for backrefering.\n");
              exit(EXIT_FAILURE);
            }
            else {
              flag = 1;
              char * curr_back = NULL;
              curr_back = strdup(back_words->words[back_words->n_words - back_int]);
              // free curr_back
              printf("%s", curr_back);
              // add the curr_back the the back_words
              back_words->n_words++;
              back_words->words = realloc(
                  back_words->words, back_words->n_words * sizeof(*back_words->words));
              back_words->words[back_words->n_words - 1] = strdup(curr_back);
              free(curr_back);
            }
          }
        }
        free(cat_int);

        // in the case we don't need to do backreference but do chooseword
        if (flag == 0) {
          const char * curr_word = chooseWord(cat_name, cat_array);
          printf("%s", curr_word);
          // add the curr_word to back_words
          back_words->n_words++;
          back_words->words = realloc(back_words->words,
                                      back_words->n_words * sizeof(*back_words->words));
          back_words->words[back_words->n_words - 1] = strdup(curr_word);
        }

        // free the realloc memory taken by cat_name
        free(cat_name);
        ptr++;
      }
      else {
        // if the character is not in the category name, then just print the character
        printf("%c", *ptr);
        ptr++;
      }
    }
  }
  free(line);

  // free part
  free_catarray_t(cat_array);
  free_category_t(back_words);
}
