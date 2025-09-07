#ifndef DOPE_DATA_TAPE_H
#define DOPE_DATA_TAPE_H

#include "dope_constants.h"
#include "dope_errors.h"
#include "dope_types.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    DOPE_DATA_INVALID,
    DOPE_DATA_NUMBER,
    DOPE_DATA_LABEL,
    DOPE_DATA_FINISH
} dope_data_type_t;

typedef union {
    dope_float_t number;                       // magnitude × 10^exponent
    dope_line_t label;
} dope_value_t;

typedef struct {
    dope_data_type_t type;
    dope_value_t value;
    dope_error_t error_code;
} dope_argument_t;

typedef struct {
    dope_argument_t* args;
    dope_size_t size;
    dope_size_t capacity;
} dope_data_t;

dope_data_t* dope_new_data(uint8_t line_count);

void dope_free_data(dope_data_t* data);

void dope_clear_arg(dope_argument_t* arg);

bool dope_is_number(char* str);

void dope_parse_number(dope_argument_t* arg);

void dope_parse_label(dope_argument_t* arg);

void dope_input_arg(dope_argument_t* arg, FILE* istream);

void dope_input_data(dope_data_t* data, FILE* istream);

void dope_print_raw_arg(dope_argument_t* arg);

void dope_print_data(dope_data_t* data);

#endif
