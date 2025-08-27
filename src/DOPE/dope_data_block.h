#ifndef DOPE_DATA_TAPE_H
#define DOPE_DATA_TAPE_H

#include "dope_constants.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    DOPE_DATA_NUMBER,
    DOPE_DATA_LABEL
} dope_data_type_t;

typedef union {
    float number;                       // magnitude × 10^exponent
    char string[DOPE_DATA_STRING_SIZE]; // string label
} dope_data_value_t;

typedef struct {
    dope_data_type_t type;
    dope_data_value_t value;
} dope_data_argument_t;

typedef struct {
    uint8_t si;  // source index (for runtime consumption)
    dope_data_argument_t* args;
    uint8_t size;
    uint8_t capacity;
} dope_data_block_t;

dope_data_block_t* dope_new_data_block(uint8_t line_count);

void dope_free_data_block(dope_data_block_t* data_block);

float dope_read_next_number(dope_data_block_t* data_block);

char* dope_read_next_label(dope_data_block_t* data_block);

uint8_t dope_input_data_value(dope_data_value_t* data_value, FILE* istream);

void dope_input_data_block(dope_data_block_t* data_block, FILE* istream);

void dope_print_data_block(dope_data_block_t* data_block);

#endif
