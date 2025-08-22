#ifndef DOPE_PROGRAM_H
#define DOPE_PROGRAM_H

#include "dope_constants.h"
#include "dope_types.h"
#include "dope_errors.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

extern const char* const DOPE_INSTRUCTIONS[];
extern const uint8_t DOPE_OPERAND_COUNT[];

typedef dope_field_t[DOPE_INSTRUCTION_PARTS] dope_instruction_record_t;

typedef struct {
    uint8_t line_number;
    uint8_t error_code;
    uint8_t opcode;             // 1–19 or 0 on error
    dope_instruction_record_t fields;
} dope_instruction_t;

typedef struct {
    int ip;                     // instruction pointer
    dope_instruction_t* instructions;
    size_t size;
    size_t capacity;
} dope_program_t;

dope_program_t* dope_new_program(size_t line_count);

void dope_free_program(dope_program_t* program);

bool dope_is_truncated(dope_line_t* line);

void dope_consume_remaining(FILE* istream);

size_t dope_read_line(dope_line_t* line, FILE* istream);

size_t dope_instruction_tokenize(dope_line_t* line, dope_field_t tokens[]);

int dope_lookup_opcode(const char* mnemonic);

void dope_input_instruction(dope_instruction_t* instruction, FILE* istream);

void dope_input_program(dope_program_t* program, FILE* stream);

void dope_print_instruction(dope_instruction_t* instruction);

void dope_print_program(dope_program_t* program);

#endif
