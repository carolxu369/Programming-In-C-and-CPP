#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

//any functions you want your main to use
catarray_t * get_catarray_t(FILE * f);
void free_catarray_t(catarray_t * cat_array);
void free_category_t(category_t * cat_word);
void print_story(FILE * f_word, FILE * f_story);
#endif
