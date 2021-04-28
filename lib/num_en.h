/* SPDX-License-Identifier: GPL-2.0-only */

#include "stdint.h"

#ifndef NUM_TRANS_NUM_EN_H
#define NUM_TRANS_NUM_EN_H

struct en_alt_words_for_twenties {
	char *num_str;
	unsigned short int value;
};

struct en_alt_words_for_hundreds {
	char *num_str;
	unsigned short int value;
};


int en_str_has_units(char str[]);
int en_str_has_tens(char str[]);
int en_str_has_from_eleven_to_fefteen(char str[]);
int en_str_has_hundreds(char str[]);
int en_str_has_thousands(char str[]);
int en_str_has_millions(char str[]);
int en_get_integer(char *app_name, char *language, char *str);
void en_input_string_is_correct(char *app_name, char *language, char *string);

#endif  /* NUM_TRANS_NUM_EN_H */
