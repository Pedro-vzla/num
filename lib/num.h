/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef NUM_TRANS_NUM_H
#define NUM_TRANS_NUM_H

#define   CONVERTION_LIMIT                  999999999

/* definitions for decimal system */
#define   UNIT       1
#define   TEN        10
#define   HUNDRED    100
#define   THOUSAND   1000
#define   MILLION    1000000

/* definitions for CLI options */
#define   OPT_HELP                          0b00000001
#define   OPT_LANGUAGE                      0b00000010
#define   OPT_TO_INTEGER                    0b00000100
#define   OPT_TO_STRING                     0b00001000

#define   OPTS_STRING_AND_INTEGER_ENABLED   0b00001100
#define   TSTR_AND_TINT_ENABLED_WITH_LANG   0b00001110
#define   ONLY_OPT_HELP_ENABLED             0b00000001
#define   NO_OPTS_SUPPLIED                  0b00000000
#define   CORRECT_TO_INT_OPTS               0b00000110

#endif /* NUM_TRANS_NUM_H */
