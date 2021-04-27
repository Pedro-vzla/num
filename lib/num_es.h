/* SPDX-License-Identifier: GPL-2.0-only */

#include "stdint.h"

#ifndef NUM_TRANS_NUM_ES_H
#define NUM_TRANS_NUM_ES_H

struct es_alt_words_for_twenties {
	char *num_str;
	unsigned short int value;
};

struct es_alt_words_for_hundreds {
	char *num_str;
	unsigned short int value;
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

#endif /* NUM_TRANS_NUM_ES_H */
