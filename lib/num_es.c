// SPDX-License-Identifier: GPL-2.0-only

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>
#include <strings.h>
/* #include <locale.h> */

#include "num_es.h"
#include "num.h"

#ifndef NUM_TRANS_NUM_ES_C
#define NUM_TRANS_NUM_ES_C

/* alternative syntax available in C99 and as a C89 extension in GCC
 
struct es_alt_words_for_twenties twenties[10] = {
	{ .num_str = "veintiuno"    , .value = 21 },
	{ .num_str = "veintiún"     , .value = 21 },
	{ .num_str = "veintidos"    , .value = 22 },
	{ .num_str = "veintitrés"   , .value = 23 },
	{ .num_str = "veinticuatro" , .value = 24 },
	{ .num_str = "veinticinco"  , .value = 25 },
	{ .num_str = "veintiséis"   , .value = 26 },
	{ .num_str = "veintisiete"  , .value = 27 },
	{ .num_str = "veintiocho"   , .value = 28 },
	{ .num_str = "veintinueve"  , .value = 29 },
};
*/

struct es_alt_words_for_twenties twenties[10] = {
	{ "veintiuno"    , 21 },
	{ "veintiún"     , 21 },
	{ "veintidos"    , 22 },
	{ "veintitrés"   , 23 },
	{ "veinticuatro" , 24 },
	{ "veinticinco"  , 25 },
	{ "veintiséis"   , 26 },
	{ "veintisiete"  , 27 },
	{ "veintiocho"   , 28 },
	{ "veintinueve"  , 29 },
};

const char es_words_for_units[10][7] = {
	"cero",
	"uno",
	"dos",
	"tres",
	"cuatro",
	"cinco",
	"seis",
	"siete",
	"ocho",
	"nueve",
};

const char es_words_from_eleven_to_fefteen[10][12] = {
	"",
	"once",
	"doce",
	"trece",
	"catorce",
	"quince",
	"dieciséis",
	"diecisiete",
	"dieciocho",
	"diecinueve",
};

const char es_words_for_tens[10][10] = {
	"",
	"diez",
	"veinte",
	"treinta",
	"cuarenta",
	"cincuenta",
	"sesenta",
	"setenta",
	"ochenta",
	"noventa",
};

const char es_words_for_hundreds[10][14] = {
	"",
	"cien",
	"doscientos",
	"trescientos",
	"cuatrocientos",
	"quinientos",
	"seiscientos",
	"setecientos",
	"ochocientos",
	"novecientos",
};

const char es_allowed_words[15][13] = {
	"un",
	"y",
	"mil",
	"millón",
	"millones",
	"veintiuno",
	"veintiún",
	"veintidos",
	"veintitrés",
	"veinticuatro",
	"veinticinco",
	"veintiséis",
	"veintisiete",
	"veintiocho",
	"veintinueve",
};

int str_has_units(char str[]) {
	int i;
	int SIZE = 10;

	for( i=0; i < SIZE; i++ ) {
		if (strcasecmp(str, es_words_for_units[i] ) == 0) {
			return i * UNIT;
		} 
		if (strcasecmp(str, "un") == 0) {
			return UNIT;
		}
	}
	return false;
}

int str_has_tens(char str[]) {
	int i;
	int SIZE = 10;

	for( i=0; i < SIZE; i++ ) {
		if (!strcasecmp(str, es_words_for_tens[i] )) {
			return i * TEN;
		}
		if (strcasecmp(str, twenties[i].num_str) == 0) {
			return twenties[i].value;
		}

	}
	return false;
}

int str_has_from_eleven_to_fefteen(char str[]) {
	int i;
	int SIZE = 10;

	for( i=1; i < SIZE; i++ ) {
		if (!strcasecmp(str, es_words_from_eleven_to_fefteen[i])) {
			return TEN + i;
		}
	}
	return false;
}

int str_has_hundreds(char str[]) {
	int i;
	int SIZE = 10;

	struct es_alt_words_for_twenties hundreds[2];

	hundreds[1].num_str = "ciento";
	hundreds[1].value = 100;

	for( i=1; i < SIZE; i++ ) {
		if (!strcasecmp(str, es_words_for_hundreds[i])) {
			return HUNDRED * i;
		}
		if (i < 2 && strcasecmp(str, hundreds[i].num_str) == 0) {
			return hundreds[i].value;
		}
	}
	return false;
}

int str_has_thousands(char str[]) {
	if (strcasecmp(str, "mil") == 0) {
		return THOUSAND;
	} else {
		return true;
	}
}

int str_has_millions(char str[]) {
	if (!strcasecmp(str, "millón")) {
		return MILLION;
	} else if(!strcasecmp(str, "millones")) {
		return MILLION;
	} else {
		return true;
	}
}

void input_string_is_correct(char *app_name, char *language, char *string){
	int i; /* arr_u=0, arr_etf=0, arr_t=0, arr_h=0; */

	if (strcasecmp(language, "es") == 0) {
		for( i=0; i<15; i++ ) {
			if (i < 10 && strcasecmp(string, es_words_for_units[i]) == 0) {
				/* arr_u = 1; */
			}
			if (i < 10 && strcasecmp(string, es_words_from_eleven_to_fefteen[i]) == 0) {
				/* arr_etf = 1; */
			}
			if (i < 10 && strcasecmp(string, es_words_for_tens[i]) == 0) {
				/* arr_t = 1; */
			}
			if ( strcasecmp(string, es_allowed_words[i]) == 0) {
				/* arr_t = 1; */
			}
			if (i < 10 && strcasecmp(string, es_words_for_hundreds[i]) == 0) {
				/* arr_h = 1; */
			}
		}

		/*
		printf("%12s u=%d etf=%d t=%d h=%d\n", string, arr_u, arr_etf, arr_t, arr_h);
		if (arr_u == 0 && arr_etf == 0 && arr_t == 0 && arr_h == 0 ) {
			fprintf(stderr, "%s: Error: \"%s\" no es un número o una palabra permitida\n", app_name, string);
			exit(EXIT_FAILURE);
		}
		*/
		
	}
}

int get_integer(char *app_name, char *language, char *str) {

	int output_int = 0;

	int million=0;
	int thousand=0;
	int hundred = 0;
	while (str != NULL) {

		input_string_is_correct(app_name, language, str);

		output_int += str_has_units(str);
		output_int += str_has_tens(str);
		output_int += str_has_from_eleven_to_fefteen(str);
		output_int += str_has_hundreds(str);
		hundred = output_int;

		if (strcasecmp(str, "millones") == 0 || strcasecmp(str, "millón") == 0) {
			million = output_int * MILLION;
			output_int = 0;
			hundred = 0;
		}

		if (strcasecmp(str, "mil") == 0) {
			if ( output_int == 0){
				output_int = 1;
			}
			thousand = output_int * str_has_thousands(str);
			output_int = 0;
			hundred = 0;
		}

		/* printf("%s=%d m=%d t=%d h=%d\n", str, output_int, million, thousand, hundred); */
		str = strtok(NULL, " ");
	}

	return million + thousand + hundred;
}

char get_string(void) {
	printf("un millón\n");
	return 0;
}

void show_help(char *bin_name){
	fprintf(stdout, "Usage: %s -s|-i [-lh] \"<integer>|<string>\"\n\n", bin_name);

	fprintf(stdout, "-s --to-string\tThe argument to this option must be a string\n");
	fprintf(stdout, "              \t containig a valid number in words\n\n");

	fprintf(stdout, "-i --to-integer\tThe argument to this option must be a integer\n");
	fprintf(stdout, "               \twhti a maximun value of 999999999\n\n");

	fprintf(stdout, "-l --language\tThe argument is a ISO-639-1 code case insensitive,\n");
	fprintf(stdout, "             \tmust be specified if -s|--tostring -i|--to-integer\n");
	fprintf(stdout, "             \tare in use\n\n");

	fprintf(stdout, "-h --help\tShow this help message\n\n");
	
	fprintf(stdout, "Example 1:\n");
	fprintf(stdout, "%s --language es --to-integer \"novecientos noventa y nueve millones uno\"\n\n", bin_name);
	fprintf(stdout, "Example 2:\n");
	fprintf(stdout, "%s -l ES -i \"novecientos veinte y un millones ciento trece mil doscientos uno\"\n\n", bin_name);

}

void to_string_arg_validation( unsigned int integer, char *endptr, char *arg, char *app_name){

	if (integer > CONVERTION_LIMIT) {
		printf("%s: Error: the maximun number to convert is: %d\n", app_name, CONVERTION_LIMIT);
		exit(EXIT_FAILURE);
	}
}

void validate_to_str_and_to_int_not_used_together(uint8_t options, char *app_name) {
	/* if (opt1 == true && opt2 == true) { */
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

	if(strcasecmp(arg, "es") != 0 && strcasecmp(arg, "en") != 0) {
		fprintf(stderr, "%s: Error: unknown or unsuported argument\n", app_name);
		fprintf(stderr, "empty or unsuported ISO-639-1 code suplied to -l|--language option\n");
		exit(EXIT_FAILURE);
	} 

	if (options == CORRECT_TO_INT_OPTS) {
		if ( strcasecmp(arg, "es") == 0 || strcasecmp(arg, "en") == 0 ) {
			printf("%d\n", get_integer(app_name, arg, tokens));
			exit(EXIT_SUCCESS);
		}			
	} 
}

#endif /* NUM_TRANS_NUM_ES_C */
