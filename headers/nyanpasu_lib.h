//
// Created by thgir on 17/04/2021.
//

#ifndef BATAILLE_NAVALE_UTBM_NYANPASU_LIB_H
#define BATAILLE_NAVALE_UTBM_NYANPASU_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void * safe_malloc(size_t n);
FILE *open_file(const char *fileName, const char *mode);
int input_word(char **word);
void clear_buffer(void);
int power_of_two(int power);
void swap(void *a, void *b, size_t len);
int str_to_int(const char * str);

#endif //BATAILLE_NAVALE_UTBM_NYANPASU_LIB_H