#ifndef DOPE_DATA_SHEET_H
#define DOPE_DATA_SHEET_H

#include "dope_constants.h"
#include "dope_types.h"
#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint8_t run;
    dope_data_field_t fields[DOPE_DATA_SHEET_FIELDS - 1];
} dope_data_line_t;

typedef struct {
    dope_data_line_t* lines;
    size_t capacity;
    size_t count;
} dope_data_sheet_t;

dope_data_sheet_t* dope_new_data_sheet(int line_count);

void dope_free_data_sheet(dope_data_sheet_t* data);

void dope_trim_field(dope_data_field_t* field);

void dope_print_data_line(dope_data_line_t* line);

void dope_print_data_sheet(dope_data_sheet_t* data);

void dope_input_data_ubyte(uint8_t * ubyte, FILE* istream);

void dope_input_data_field(dope_data_field_t* field, FILE* istream);

void dope_input_data_line(dope_data_line_t* line, FILE* istream);

void dope_input_data_sheet(dope_data_sheet_t* data, FILE* istream);

#endif
