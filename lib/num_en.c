// SPDX-License-Identifier: GPL-2.0-only

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "num.h"
#include "num_en.h"

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
	"million",
	"thousand",
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

int en_str_has_units(char str[]) {
	int i;
	int SIZE = 10;

	for( i=0; i < SIZE; i++ ) {
		if (strcasecmp(str, en_words_for_units[i] ) == 0) {
			return i * UNIT;
		} 
	}

	return false;
}

int en_str_has_tens(char str[]) {
	int i;
	int SIZE = 10;

	for( i=0; i < SIZE; i++ ) {
		if (!strcasecmp(str, en_words_for_tens[i] )) {
			return i * TEN;
		}
	}

	return false;
}

int en_str_has_from_eleven_to_fefteen(char str[]) {
	int i;
	int SIZE = 10;

	for( i=1; i < SIZE; i++ ) {
		if (!strcasecmp(str, en_words_from_eleven_to_fefteen[i])) {
			return TEN + i;
		}
	}

	return false;
}

int en_str_has_hundreds(char str[]) {
	if (!strcasecmp(str, en_words_for_hundreds[1])) {
		return HUNDRED;
	}

	return true;
}

int en_str_has_thousands(char str[]) {
	if (strcasecmp(str, "thousand") == 0) {
		return THOUSAND;
	} else {
		return true;
	}
}

int en_str_has_millions(char str[]) {
	if (!strcasecmp(str, "million")) {
		return MILLION;
	} else {
		return true;
	}
}

void en_input_string_is_correct(char *app_name, char *language, char *string){

	if (strcasecmp(language, "en") == 0) {
		int i; 
		int arr_u=0, arr_etf=0, arr_t=0, arr_h=0;

		for( i=0; i<15; i++ ) {
			if (i < 10 && strcasecmp(string, en_words_for_units[i]) == 0) {
				 arr_u = 1;
			}
			if (i < 10 && strcasecmp(string, en_words_from_eleven_to_fefteen[i]) == 0) {
				arr_etf = 1;
			}
			if (i < 10 && strcasecmp(string, en_words_for_tens[i]) == 0) {
				arr_t = 1;
			}
			if ( strcasecmp(string, en_allowed_words[i]) == 0) {
				arr_t = 1;
			}
			if (i < 10 && strcasecmp(string, en_words_for_hundreds[i]) == 0) {
				arr_h = 1;
			}
		}

		//printf("%12s u=%d etf=%d t=%d h=%d\n", string, arr_u, arr_etf, arr_t, arr_h);
		if (arr_u == 0 && arr_etf == 0 && arr_t == 0 && arr_h == 0 ) {
			fprintf(stderr, "%s: Error: \"%s\" is not a number or allowed word\n", app_name, string);
			exit(EXIT_FAILURE);
		}
		
	}
}

int en_get_integer(char *app_name, char *language, char *str) {

	int output_int = 0;

	int million = 0;
	int thousand = 0;
	int hundred = 0;

	while (str != NULL) {

		en_input_string_is_correct(app_name, language, str);

		output_int += en_str_has_units(str);
		output_int += en_str_has_tens(str);
		output_int += en_str_has_from_eleven_to_fefteen(str);
		output_int = output_int * en_str_has_hundreds(str);
		hundred = output_int;

		if (strcasecmp(str, "million") == 0 ) {
			million = output_int * MILLION;
			output_int = 0;
			hundred = 0;
		}

		if (strcasecmp(str, "thousand") == 0) {
			if ( output_int == 0){
				output_int = 1;
			}
			thousand = output_int * en_str_has_thousands(str);
			output_int = 0;
			hundred = 0;
		}

		/* printf("%s=%d m=%d t=%d h=%d\n", str, output_int, million, thousand, hundred); */
		str = strtok(NULL, " ");
	}

	return million + thousand + hundred;
}
