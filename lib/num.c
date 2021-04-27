/* SPDX-License-Identifier: GPL-2.0-only */

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

num.c - When assembly of "num" starts
Last modified: 2021-04-13 18:46:12

Copyright (c) 2021 Pedro Rondón <pedroprondonr@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
/*#include <locale.h>*/
#include "num.h"
#include "num_es.h"
/*#include "lib/num_en.h"*/

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
				// maybe put the value of optarg to a static variable to 
				// use among various functions
				tokens = strtok(optarg, " ");
				break;
			case 'l':
				cli_opts |= OPT_LANGUAGE;
				language = optarg;
				/*
				if (strcasecmp(language, "es")) {
					setlocale(LC_ALL, "es_CL");
				}
				if (strcasecmp(language, "en")) {
					setlocale(LC_ALL, "en_US");
				}*/
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
	/*printf("to-string=%d to-integer=%d languague=%d help=%d\n", opt_to_string, opt_to_integer, opt_languague, opt_help);*/
	validate_to_str_and_to_int_not_used_together(cli_opts, app_name);
	validate_help_opt(cli_opts, app_name);
	validate_empty_opts(cli_opts, app_name);

	validate_to_integer_opt(language, app_name, cli_opts, tokens);
	/*printf("%s\n", tokens);*/


	/*
	if (opt_help == false && opt_languague == true && opt_to_integer == false && opt_to_string == true ) {
		if ( (strcmp(language, "es") == 0 || strcmp(language, "en") == 0) && integer ) {
			get_string();
			exit(EXIT_SUCCESS);
		} else {
			fprintf(stderr, "%s: Error: invalid ISO-639-1 code suplied to -l|--language option", app_name);
			exit(EXIT_FAILURE);
		}
	} 

	if (opt_help == false && opt_languague == true && opt_to_integer == false && opt_to_string == false ) {
		fprintf(stderr, "%s: Error: option -i|--to-integer or -s|--to-integer not especified\n", app_name);
		exit(EXIT_FAILURE);
	} 

	if (opt_help == false && opt_languague == false && opt_to_integer == false && opt_to_string == false ) {
	}
	*/
	return 0;
}
