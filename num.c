// SPDX-License-Identifier: GPL-2.0-only

/*
+----------------------------------------------------------------------------+
| This program is free software; you can redistribute it and/or modify it    |
| under the terms of the GNU General Public License as published by the      |
| Free Software Foundation; version 2.                                       |
|                                                                            |
| This program is distributed in the hope that it will be useful, but        |
| WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY |
| or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License    |
| for more details.                                                          |
|                                                                            |
| You should have received a copy of the GNU General Public License          |
| along with this program. If not, see <https://www.gnu.org/licenses/>.      |
+----------------------------------------------------------------------------+

main.c - When assembly of "num" starts
Last modified: 2021-04-13 18:46:12

Copyright (c) 2021 Pedro Rondón <pedroprondonr@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>
#include "lib/num.h"

int str_has_units(char str[]);
int str_has_tens(char str[]);
int str_has_from_eleven_to_fefteen(char str[]);
int str_has_thousands(char str[]);
int str_has_millions(char str[]);
int get_integer(char *str);
char get_string(void);
void show_help(char *bin_name);
void to_string_arg_validation( unsigned int integer, char *endptr, char *arg, char *app_name);
void validate_to_str_and_to_int_not_used_together(uint8_t options, char *app_name);
void validate_help_opt(uint8_t options, char *app_name);
void validate_empty_opts(uint8_t options, char *app_name);
void validate_to_integer_opt(char * arg, char *app_name, uint8_t options, char *tokens);
int main(int argc, char *argv[]);

int str_has_units(char str[]) {
	int i;
	int SIZE = 10;

	for( i=0; i < SIZE; i++ ) {
		if (!strcmp(str, es_words_for_units[i] )) {
			return i * UNIT;
		}
	}
	return false;
}

int str_has_tens(char str[]) {
	int i;
	int SIZE = 10;

	for( i=0; i < SIZE; i++ ) {
		if (!strcmp(str, es_words_for_tens[i] )) {
			return i * TEN;
		}
	}
	return false;
}

int str_has_from_eleven_to_fefteen(char str[]) {
	int i;
	int SIZE = 6;

	for( i=1; i < SIZE; i++ ) {
		if (!strcmp(str, es_words_from_eleven_to_fefteen[i])) {
			return TEN + i;
		}
	}
	return false;
}

int str_has_hundreds(char str[]) {
	int i;
	int SIZE = 10;

	for( i=1; i < SIZE; i++ ) {
		if (!strcmp(str, es_words_for_hundreds[i])) {
			return HUNDRED * i;
		}
	}
	return false;
}

int str_has_thousands(char str[]) {
	if (!strcmp(str, "mil")) {
		return THOUSAND;
	} else {
		return true;
	}
}

int str_has_millions(char str[]) {
	if (!strcmp(str, "millón")) {
		return MILLION;
	} else if(!strcmp(str, "millones")) {
		return MILLION;
	} else {
		return true;
	}
}

int get_integer(char *str) {

	int output_int = 0;

	int million=0;
	int thousand=0;
	int hundred = 0;
	while (str != NULL) {

		output_int += str_has_units(str);
		output_int += str_has_tens(str);
		output_int += str_has_from_eleven_to_fefteen(str);
		output_int += str_has_hundreds(str);
		hundred = output_int;

		if (strcmp(str, "millones") == 0 || strcmp(str, "millón") == 0) {
			million = output_int * MILLION;
			output_int = 0;
		}

		if (strcmp(str, "mil") == 0) {
			if ( output_int == 0){
				output_int = 1;
			}
			thousand = output_int * str_has_thousands(str);
			output_int = 0;
			hundred = 0;
		}

		//printf("%s=%d m=%d t=%d h=%d\n", str, output_int, million, thousand, hundred);
		str = strtok(NULL, " ");
	}

	return million + thousand + hundred;
}

char get_string(void) {
	printf("un millón\n");
	return 0;
}

void show_help(char *bin_name){
	fprintf(stderr, "Usage: %s -s|-i [-lh] \"<integer>|<string>\"\n", bin_name);
}

void to_string_arg_validation( unsigned int integer, char *endptr, char *arg, char *app_name){

	if (integer > CONVERTION_LIMIT) {
		printf("%s: Error: the maximun number to convert is: %d\n", app_name, CONVERTION_LIMIT);
		exit(EXIT_FAILURE);
	}
}

void validate_to_str_and_to_int_not_used_together(uint8_t options, char *app_name) {
	//if (opt1 == true && opt2 == true) {
	if (options == OPTS_STRING_AND_INTEGER_ENABLED || options == TSTR_AND_TINT_ENABLED_WITH_LANG) {
		fprintf(stderr, "%s: Error: options -s|--to-string and -i|--to-integer can not be used together\n", app_name);
		exit(EXIT_FAILURE);
	}
}

void validate_help_opt(uint8_t options, char *app_name) {
	if ((options & OPT_HELP) == ONLY_OPT_HELP_ENABLED) {
		show_help(app_name);
		exit(EXIT_SUCCESS);
	}
}

void validate_empty_opts(uint8_t options, char *app_name) {
	if (options == NO_OPTS_SUPPLIED) {
		show_help(app_name);
		exit(EXIT_FAILURE);
	}
}

void validate_to_integer_opt(char * arg, char *app_name, uint8_t options, char *tokens) {
	if (!(options & OPT_LANGUAGE)) {
		fprintf(stderr, "%s: Error: missing -l|--language option\n", app_name);
		fprintf(stderr, "option -i|--to-integer needs ");
		fprintf(stderr, "to be used with -l|--language option\n");
		exit(EXIT_FAILURE);
	}

	if(strcmp(arg, "es") != 0 && strcmp(arg, "en") != 0) {
		fprintf(stderr, "%s: Error: unknown or unsuported argument\n", app_name);
		fprintf(stderr, "empty or unsuported ISO-639-1 code suplied to -l|--language option\n");
		exit(EXIT_FAILURE);
	} 

	if (options == CORRECT_TO_INT_OPTS) {
		if ( strcmp(arg, "es") == 0 || strcmp(arg, "en") == 0 ) {
			printf("%d\n", get_integer(tokens));
			exit(EXIT_SUCCESS);
		}			
	} 
}


int main(int argc, char *argv[]) {
	unsigned int integer;
	int c;
	char *tokens, *endptr, *language;
	char *app_name = argv[0];
	uint8_t cli_opts = 0;

	while (argc > 0) {
		int option_index = 0;
		static struct option long_options[] = {
			{"to-string"  , required_argument , 0 , 's' } ,
			{"to-integer" , required_argument , 0 , 'i' } ,
			{"language"   , required_argument , 0 , 'l' } ,
			{"help"       , no_argument       , 0 , 'h' } ,
		};

		c = getopt_long(argc, argv, "s:i:l:h",
				long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
			case 's':
				cli_opts |= OPT_TO_STRING;
				integer = strtol(optarg, &endptr, 10);
				to_string_arg_validation(integer, endptr, optarg, app_name);
				break;
			case 'i':
				cli_opts |= OPT_TO_INTEGER;
				tokens = strtok(optarg, " ");
				break;
			case 'l':
				cli_opts |= OPT_LANGUAGE;
				language = optarg;
				break;
			case 'h':
				cli_opts |= OPT_HELP;
				break;
			case '?':
				fprintf(stderr, "%s: Enter: %s --help to view usage\n", app_name, app_name);
				exit(EXIT_FAILURE);
				break;
			default:
				show_help(app_name);
				exit(EXIT_FAILURE);
				break;
		}
	}
	//printf("to-string=%d to-integer=%d languague=%d help=%d\n", opt_to_string, opt_to_integer, opt_languague, opt_help);
	validate_to_str_and_to_int_not_used_together(cli_opts, app_name);
	validate_help_opt(cli_opts, app_name);
	validate_empty_opts(cli_opts, app_name);
	validate_to_integer_opt(language, app_name, cli_opts, tokens);


	//if (opt_help == false && opt_languague == true && opt_to_integer == false && opt_to_string == true ) {
	//	if ( (strcmp(language, "es") == 0 || strcmp(language, "en") == 0) && integer ) {
	//		get_string();
	//		exit(EXIT_SUCCESS);
	//	} else {
	//		fprintf(stderr, "%s: Error: invalid ISO-639-1 code suplied to -l|--language option", app_name);
	//		exit(EXIT_FAILURE);
	//	}
	//} 

	//if (opt_help == false && opt_languague == true && opt_to_integer == false && opt_to_string == false ) {
	//	fprintf(stderr, "%s: Error: option -i|--to-integer or -s|--to-integer not especified\n", app_name);
	//	exit(EXIT_FAILURE);
	//} 

	//if (opt_help == false && opt_languague == false && opt_to_integer == false && opt_to_string == false ) {
	//}
	return 0;
}
