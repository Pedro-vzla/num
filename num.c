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
#include "lib/num.h"

int str_has_units(char str[]) {
	int i;
	int SIZE = 10;

	for( i=0; i < SIZE; i++ ) {
		if (!strcmp(str, es_words_for_units[i] )) {
			return i;
		}
	}
	return false;
}

int str_has_tens(char str[]) {
	int i;
	int TEN = 10;
	int SIZE = 10;

	for( i=0; i < SIZE; i++ ) {
		if (!strcmp(str, es_words_for_tens[i] )) {
			return i * TEN;
		}
	}
	return false;
}

int get_integer(char *str) {
	int output_int = 0;
	while (str != NULL) {
		if (str_has_tens(str)) {
			output_int += str_has_tens(str);
		}
		if (str_has_units(str)) {
			output_int += str_has_units(str);
		}
		str = strtok(NULL, " ");
	}

	return output_int;
}

void show_help(char *bin_name){
	printf("Usage: %s -s|-i [-jh] \"<string>\"\n", bin_name);
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
	int c;
	char *tokens;

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
				printf("option %c\n", c);
				break;

			case 'i':
				tokens = strtok(optarg, " ");
				printf("%d\n", get_integer(tokens));
				break;

			case 'l':
				printf("option \n");
				break;

			case 'h':
				show_help(argv[0]);
				break;

			case '?':
				printf("%s: Enter: %s --help to view usage\n", argv[0], argv[0]);
				exit(EXIT_FAILURE);
				break;

			default:
				show_help(argv[0]);
				exit(EXIT_FAILURE);
				break;
		}
	}
	return 0;
}
