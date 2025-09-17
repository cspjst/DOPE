/**
* Cut down regex implentation for input validation
* Subset:
* ASCII    Char    Purpose
*  36	     $	    Anchor: Matches the end of the input string.
*  42	     *	    Quantifier: Matches 0 or more of the preceding element.
*  43	     +	    Quantifier: Matches 1 or more of the preceding element.
*  45	     -	    Range operator: Defines a range inside a character class (e.g., a-z).
*  46	     .	    Wildcard: Matches any single character.
*  63	     ?	    Quantifier: Matches 0 or 1 of the preceding element.
*  91	     [	    Starts a character class.
*  92	     \	    Escape character: Forces the next character to be treated as literal.
*  93	     ]	    Ends a character class.
*  94	     ^	    Anchor: Matches the start of the input string.
*/
#ifndef PARSE_REGEX_H
#define PARSE_REGEX_H

#include <stdbool.h>

typedef bool (*dope_regex_fn_t)(const char **rgx, const char **str);

// sparse dispatch table - size 59 for chars from '$' - '$' to '^' - '$'
static parse_regex_fn_t parse_regex_dispatch_table[59] = {0};
static bool is_init_dispatch_table = false;

void parse_regex_init_dispatch_table(); 

bool parse_regex(const char* regex, const char* string);

bool parse_regex_dispatch(const char **rgx, const char **str);

// regex token parse functions:
bool parse_anchor_start(const char **rgx, const char **str);

bool parse_anchor_end(const char **rgx, const char **str);

bool parse_wildcard(const char **rgx, const char **str);

bool parse_literal(const char **rgx, const char **str, char expected);

#endif
