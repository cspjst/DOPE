/**
* Cut down regex implentation for input validation
* Subset:
* 
*/
#ifndef PARSE_REGEX_H
#define PARSE_REGEX_H

#include <stdbool.h>

typedef bool (*dope_regex_fn_t)(const char **rgx, const char **str, char expected);

// sparse dispatch table - size 59 for chars from '$' - '$' to '^' - '$'
static parse_regex_fn_t parse_regex_fn_call_table[59] = {0};

void parse_regex_init_call_table(); 

bool parse_regex_match(const char **regex_ptr, const char **text_ptr)

// Main entry point: checks if the entire text matches the regex
bool parse_regex(const char *regex, const char *text) {
    return parse_regex_match(rgx, str);
}

bool match_caret(const char **rgx, const char **str, char expected);

bool match_dollar(const char **rgx, const char **str, char expected);

bool match_dot(const char **rgx, const char **str, char expected);

bool match_literal(const char **rgx, const char **str, char expected);

#endif
