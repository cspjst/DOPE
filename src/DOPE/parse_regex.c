#include "parse_regex.h" 

 {
    return parse_regex_dispatch(rgx, str);
}

dope_test_match
bool match_here(const char **regex_ptr, const char **text_ptr) {
    // Loop until the entire regex pattern is consumed
    while (**regex_ptr != '\0') {
        char regex_char = **regex_ptr;
        int index = regex_char - 36; // Calculate index for dispatch table

        // Check if the character is a known metacharacter with a handler
        if (index >= 0 && index < 59 && dispatch_table[index] != NULL) {
            // Call the specific handler for this metacharacter
            if (!dispatch_table[index](regex_ptr, text_ptr)) {
                return false; // Handler failed, so overall match fails
            }
        } else {
            // It's not a metacharacter; treat it as a literal
            if (!handle_literal(regex_ptr, text_ptr, regex_char)) {
                return false; // Literal character didn't match
            }
        }
    }
    // Entire regex pattern was consumed successfully
    return true;
}

// Main entry point: checks if the entire text matches the regex
bool match(const char *regex, const char *text) {
    init_dispatch_table(); // Initialize the jump table
    const char *regex_ptr = regex;
    const char *text_ptr = text;
    return match_here(&regex_ptr, &text_ptr);
}

// Handler for '^' (anchor: start of string)
bool handle_caret(const char **regex_ptr, const char **text_ptr) {
    // Check if we are at the very start of the text
    if (**text_ptr != '\0') { // If text is not empty, we're at the start
        (*regex_ptr)++; // Consume the '^' from the regex pattern
        return true;
    } else {
        // Text is empty, not at start -> fail
        return false;
    }
}

// Handler for '$' (anchor: end of string)
bool handle_dollar(const char **regex_ptr, const char **text_ptr) {
    // Check if we are at the end of the text (\0)
    if (**text_ptr == '\0') {
        (*regex_ptr)++; // Consume the '$' from the regex pattern
        return true;
    } else {
        return false; // Not at end -> fail
    }
}

// Handler for '.' (wildcard: any character)
bool handle_dot(const char **regex_ptr, const char **text_ptr) {
    // Check if there is any character to match (not \0)
    if (**text_ptr == '\0') {
        return false; // Cannot match any character if text is empty
    }
    // It matches! Consume the regex metachar and one text char.
    (*regex_ptr)++;
    (*text_ptr)++;
    return true;
}

// Default handler for literal characters (not in dispatch table)
bool handle_literal(const char **regex_ptr, const char **text_ptr, char expected_char) {
    if (**text_ptr != expected_char) {
        return false; // Literal character mismatch
    }
    // Match! Consume one char from both regex and text.
    (*regex_ptr)++;
    (*text_ptr)++;
    return true;
}
