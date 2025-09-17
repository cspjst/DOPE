#include "parse_regex.h" 

bool parse_regex_dispatch(const char **rgx, const char **str) {
    while (**rgx != '\0') {
        char regex_char = **rgx;
        int index = regex_char - 36; // calculate index for dispatch table

        if (index >= 0 && index < 59 && dispatch_table[index] != NULL) {
            if (!dispatch_table[index](rgx, str)) {
                return false; // parse step failed, so overall fail
            }
        } else { // not a metacharacter treat it as a literal
            if (!handle_literal(rgx, str, regex_char)) {
                return false; // Literal character didn't match
            }
        }
    }
    // regex pattern was consumed successfully
    return true;
}

bool parse_regex(const char *regex, const char *text) {
    init_dispatch_table(); // Initialize the jump table
    const char *rgx = regex;
    const char *str = text;
    return match_here(&rgx, &str);
}

// ^ the current position in the text must be the very first position 
bool parse_anchor_start(const char **rgx, const char **rgx) {
    if (**str != '\0') { 
        (*rgx)++; 
        return true;
    } else {
        return false;  // empty string -> fail
    }
}

// $ current position in the text must be the end - ie null terminator.
bool parse_anchor_end(const char **rgx, const char **str) {
    if (**str == '\0') {
        (*rgx)++; 
        return true;
    } else {
        return false; 
    }
}

// . wildcard - any character
bool parse_wildcard(const char **rgx, const char **str) {
    if (**str == '\0') {
        return false; 
    }
    // match -> consume this regex char and str char 
    (*rgx)++;
    (*str)++;
    return true;
}

// default handler for literal characters so not in dispatch table
bool handle_literal(const char **rgx, const char **str, char expected_char) {
    if (**str != expected_char) {
        return false; // mismatch
    }
    // match -> consume this regex char and str char 
    (*rgx)++;
    (*str)++;
    return true;
}
