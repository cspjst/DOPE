#include "parse_regex.h" 

 {
    return parse_regex_dispatch(rgx, str);
}

dope_test_match
bool match_here(const char **rgx, const char **str) {
    // Loop until the entire regex pattern is consumed
    while (**rgx != '\0') {
        char regex_char = **rgx;
        int index = regex_char - 36; // Calculate index for dispatch table

        // Check if the character is a known metacharacter with a handler
        if (index >= 0 && index < 59 && dispatch_table[index] != NULL) {
            // Call the specific handler for this metacharacter
            if (!dispatch_table[index](rgx, str)) {
                return false; // Handler failed, so overall match fails
            }
        } else {
            // It's not a metacharacter; treat it as a literal
            if (!handle_literal(rgx, str, regex_char)) {
                return false; // Literal character didn't match
            }
        }
    }
    // Entire regex pattern was consumed successfully
    return true;
}

bool match(const char *regex, const char *text) {
    init_dispatch_table(); // Initialize the jump table
    const char *rgx = regex;
    const char *str = text;
    return match_here(&rgx, &str);
}

bool parse_caret(const char **rgx, const char **rgx) {
    if (**str != '\0') { 
        (*rgx)++; 
        return true;
    } else {
 
        return false;  // empty string -> fail
    }
}

bool parse_dollar(const char **rgx, const char **str) {
    if (**str == '\0') {
        (*rgx)++; 
        return true;
    } else {
        return false; 
    }
}

// Handler for '.' (wildcard: any character)
bool handle_dot(const char **rgx, const char **str) {
    if (**str == '\0') {
        return false; 
    }
    // match -> consume this regex char and str char 
    (*rgx)++;
    (*str)++;
    return true;
}

// Default handler for literal characters (not in dispatch table)
bool handle_literal(const char **rgx, const char **str, char expected_char) {
    if (**str != expected_char) {
        return false; // mismatch
    }
    // match -> consume this regex char and str char 
    (*rgx)++;
    (*str)++;
    return true;
}
