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
#include "num.h"
#include "num_es.h"

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
	validate_to_str_and_to_int_not_used_together(cli_opts, app_name);
	validate_help_opt(cli_opts, app_name);
	validate_empty_opts(cli_opts, app_name);

	validate_to_integer_opt(language, app_name, cli_opts, tokens);

	return 0;
}
