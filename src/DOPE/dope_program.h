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

typedef dope_field_t dope_instruction_record_t[DOPE_INSTRUCTION_PARTS];

typedef struct {
    dope_opcode_t opcode;
    dope_error_t error_code;
    dope_instruction_record_t fields;
} dope_instruction_t;

typedef struct {
    dope_size_t ip;
    dope_instruction_t* instructions;
    dope_size_t size;
    dope_size_t capacity;
} dope_program_t;

dope_program_t* dope_new_program(uint8_t line_count);

void dope_free_program(dope_program_t* program);

void dope_clear_instruction(dope_instruction_t* instruction);

dope_size_t dope_instruction_tokenize(dope_line_t* line, dope_field_t tokens[]);

dope_size_t dope_lookup_opcode(const char* mnemonic);

void dope_input_instruction(dope_instruction_t* instruction, FILE* istream);

void dope_input_program(dope_program_t* program, FILE* istream);

dope_opcode_t dope_opcode(dope_program_t* program);

const dope_size_t dope_field_to_line_number(const dope_program_t* program, int i);

const dope_float_t dope_field_to_constant(const dope_program_t* program, int i);

const char* dope_field_to_str(const dope_program_t* program, int i);

void dope_print_program_line(const dope_instruction_t* instruction, FILE* ostream);

void dope_print_program(const dope_program_t* program, FILE* ostream);

#endif
