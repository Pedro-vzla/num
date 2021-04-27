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

const char en_words_for_units[10][6] = {
	"zero",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
};

const char en_words_from_eleven_to_fefteen[10][10] = {
	"",
	"eleven",
	"twelve",
	"thirteen",
	"fourteen",
	"fifteen",
	"sixteen",
	"seventeen",
	"eighteen",
	"nineteen",
};

const char en_words_for_tens[10][10] = {
	"",
	"ten",
	"twenty",
	"thirty",
	"forty",
	"fifty",
	"sixty",
	"seventy",
	"eighty",
	"ninety",
};

const char en_words_for_hundreds[2][8] = {
	"",
	"hundred",
};

const char en_allowed_words[15][13] = {
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
};

int str_has_units(char str[]);
int str_has_tens(char str[]);
int str_has_from_eleven_to_fefteen(char str[]);
int str_has_thousands(char str[]);
int str_has_millions(char str[]);
int get_integer(char *app_name, char *language, char *str);
char get_string(void);
void show_help(char *bin_name);
void to_string_arg_validation( unsigned int integer, char *endptr, char *arg, char *app_name);
void validate_to_str_and_to_int_not_used_together(uint8_t options, char *app_name);
void validate_help_opt(uint8_t options, char *app_name);
void validate_empty_opts(uint8_t options, char *app_name);
void validate_to_integer_opt(char * arg, char *app_name, uint8_t options, char *tokens);

#endif  /* NUM_TRANS_NUM_EN_H */
