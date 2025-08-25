#ifndef DOPE_DATA_TAPE_H
#define DOPE_DATA_TAPE_H

#include "dope_constants.h"
#include <stdint.h>
#include <stdio.h>

typedef char dope_data_field_t[DOPE_DATA_FIELD_SIZE];

typedef struct {
    uint8_t si;                     // source index
    dope_data_field_t* fields;
    uint8_t size;
    uint8_t capacity;
} dope_data_block_t;

dope_data_block_t dope_new_data_block(uint8_t line_count);

void dope_free_data_block(dope_data_block_t* data_block);

float dope_read_magnitude(dope_data_block_t* data_block);

char* dope_read_label(dope_data_block_t* data_block);

void dope_input_data_field(dope_data_field_t data_field, FILE* stream);

void dope_input_data_block(dope_data_block_t* data_block, FILE* stream);

#endif
