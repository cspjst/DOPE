#ifndef DOPE_UTILITY_H
#define DOPE_UTILITY_H

#include "dope_types.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

float power_of_10(int exp);

bool dope_is_truncated(dope_line_t* line);

void dope_consume_remaining(FILE* istream);

void dope_string_toupper(char* str);

dope_size_t dope_read_line(dope_line_t* line, FILE* istream);

bool dope_has_space(const char* str);

inline bool dope_is_number(char* str) {
    return (*str == '+' || *str== '-' || isdigit(*str));
}

#endif
