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
    DOPE_DATA_LABEL
} dope_data_type_t;

typedef union {
    float number;                       // magnitude × 10^exponent
    dope_line_t label;
} dope_value_t;

typedef struct {
    dope_data_type_t type;
    dope_value_t value;
    dope_error_t error_code;
} dope_argument_t;

typedef struct {
    uint8_t si;  // source index (for runtime consumption)
    dope_argument_t* args;
    uint8_t size;
    uint8_t capacity;
} dope_data_block_t;

dope_data_block_t* dope_new_data_block(uint8_t line_count);

void dope_free_data_block(dope_data_block_t* data_block);

void dope_clear_data(dope_argument_t* arg);

bool dope_is_number(char* str);

void dope_parse_mag(dope_argument_t* arg, char* magnitude);

void dope_parse_exp(dope_argument_t* arg, char* exponent);

void dope_parse_number(dope_argument_t* arg);

void dope_input_argument(dope_argument_t* arg, FILE* istream);

void dope_input_data_block(dope_data_block_t* data_block, FILE* istream);

void dope_print_arg(dope_argument_t* arg);

#endif
