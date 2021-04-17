// SPDX-License-Identifier: GPL-2.0-only

#define   CONVERTION_LIMIT                  999999999

// definitions for decimal system
#define   UNIT       1
#define   TEN        10
#define   HUNDRED    100
#define   THOUSAND   1000
#define   MILLION    1000000

// definitions for CLI options
#define   OPT_HELP                          0b00000001
#define   OPT_LANGUAGE                      0b00000010
#define   OPT_TO_INTEGER                    0b00000100
#define   OPT_TO_STRING                     0b00001000

#define   OPTS_STRING_AND_INTEGER_ENABLED   0b00001100
#define   TSTR_AND_TINT_ENABLED_WITH_LANG   0b00001110
#define   ONLY_OPT_HELP_ENABLED             0b00000001
#define   NO_OPTS_SUPPLIED                  0b00000000
#define   CORRECT_TO_INT_OPTS               0b00000110

const int digit[10] = {0,1,2,3,4,5,6,7,8,9};

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

const char es_words_from_eleven_to_fefteen[6][8] = {
	"",
	"once",
	"doce",
	"trece",
	"catorce",
	"quince",
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

