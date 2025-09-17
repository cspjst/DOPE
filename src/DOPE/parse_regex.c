#include "parse_regex.h"
#include <stdlib.h>

void parse_regex_init_dispatch_table(void) {
    dispatch_table['^' - '$'] = parse_anchor_start;
    dispatch_table['$' - '$'] = parse_anchor_end;
    dispatch_table['.' - '$'] = parse_wildcard;
    dispatch_table['\\' - '$'] = parse_escape;
    is_init_dispatch_table = true;
}

bool parse_regex(const char* regex, const char* string) {
    const char* rgx = regex;
    const char* str = string;
    // 1. strictly an empty pattern only matches an empty string
    if (*rgx == '\0') {
        return (*str == '\0');
    }
    // 2. initialize the function table
    if(!is_init_dispatch_table) {
        parse_regex_init_dispatch_table();
    }
    // 3. parse the pattern and its metatokens
    return parse_regex_dispatch(&rgx, &str);
}

bool parse_regex_dispatch(const char** rgx, const char** str) {
    while (**rgx != '\0') {
        char regex_char = **rgx;
        int index = regex_char - '$'; // calculate index for dispatch table

        if (index >= 0 && index < 59 && dispatch_table[index] != NULL) {
            if (!dispatch_table[index](rgx, str)) {
                return false; // parse step failed, so overall fail
            }
        } else { // not a metacharacter treat it as a literal
            if (!parse_literal(rgx, str, regex_char)) {
                return false; // literal character no match
            }
        }
    }
    // regex pattern was consumed successfully
    return true;
}

// ^ the current position in the text must be the very first position
bool parse_anchor_start(const char** rgx, const char** str) {
    if (**str != '\0') {
        (*rgx)++;
        return true;
    } else {
        return false;  // empty string -> fail
    }
}

// $ current position in the text must be the end - ie null terminator.
bool parse_anchor_end(const char** rgx, const char** str) {
    if (**str == '\0') {
        (*rgx)++;
        return true;
    } else {
        return false;
    }
}

// . wildcard - any character
bool parse_wildcard(const char** rgx, const char** str) {
    if (**str == '\0') {
        return false;   // mismatch
    }
    // match -> consume this regex char and str char
    (*rgx)++;
    (*str)++;
    return true;
}

// \ escape - interpret metacharacters as literals
bool parse_escape(const char** rgx, const char** str) {
    (*rgx)++; // consume escape char
    if (**rgx == '\0') {
        return false; // invalid - escape at end of string!
    }
    char lit = **rgx;
    if (**str != lit) {
        return false; // escaped character did not match
    }
    (*rgx)++;
    (*str)++;
    return true; // match
}

// * quantifier - matches 0 or more of the preceding element
bool parse_kleene_star(const char** rgx, const char** str) {
    char q = *((*rgx) - 1);
    const char** pos = rgx;
}

// default handler for literal characters so not in dispatch table
bool parse_literal(const char** rgx, const char** str, char exp) {
    if (**str != exp) {
        return false;
    }
    (*rgx)++;
    (*str)++;
    return true;
}
