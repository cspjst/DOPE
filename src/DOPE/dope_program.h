#ifndef DOPE_PROGRAM_H
#define DOPE_PROGRAM_H

#include "dope_constants.h"
#include "dope_types.h"
#include <stdint.h>

static const char* DOPE_INSTRUCTIONS[] = {
    "+", "-", ".", "/", ";", "SQR", "EXP", "LOG", "SIN",
    "C", "T", "A", "P", "N", "J", "Z", "E", "F", "S"
};

static const uint8_t DOPE_FEILDS[] = {
    3, 3, 3, 3, 2, 2, 2, 2, 2,
    5, 1, 0, 1, 0, 1, 3, 0, 0, 0
};

typedef struct {
    uint8_t line;
    uint8_t instr;
    dope_data_field_t fields[DOPE_INSTRUCTION_FIELDS];
} dope_token_t;

typedef struct {
    uint8_t ip;
    dope_token_t tokens[DOPE_PROGRAM_LINES_MAX];
} dope_program_t;

dope_program_t* dope_new_program();

void dope_free_program(dope_program_t* program);

void dope_tokenize_line(dope_line_t* line, dope_token_t* token);

#endif
