#ifndef DOPE_SHEET_H
#define DOPE_SHEET_H

#include "dope_types.h"
#include <stdio.h>

typedef dope_line_t dope_sheet_t[DOPE_PROGRAM_LINES_MAX];

dope_sheet_t* dope_new_sheet();

void dope_free_sheet(dope_sheet_t* program);

void dope_print_sheet(dope_sheet_t* program);

void dope_trim_line(dope_line_t* line);

void dope_input_line(dope_line_t* line, FILE* istream);

void dope_input_sheet(dope_sheet_t* program, FILE* istream);

#endif
