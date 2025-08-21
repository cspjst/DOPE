#ifndef DOPE_PROGRAM_H
#define DOPE_PROGRAM_H

#include "dope_constants.h"
#include "dope_types.h"
#include <stdint.h>
#include <stdbool.h>

extern const char* const DOPE_INSTRUCTIONS[];
extern const uint8_t DOPE_OPERAND_COUNT[];

typedef enum {
    DOPE_ERR_SUCCESS = 0,
    DOPE_ERR_NO_INPUT,        // EOF
    DOPE_ERR_NO_INSTR,        // empty line
    DOPE_ERR_UNKNOWN_INSTR,   // invalid instruction
    DOPE_ERR_TOO_FEW_ARGS,    // not enough operands
    DOPE_ERR_TOO_MANY_ARGS,   // too many operands
    DOPE_ERR_LINE_TOO_LONG    // input line too long
} dope_error_t;

typedef struct {
    uint8_t line_number;           
    uint8_t error_code;
    uint8_t opcode;           // 1–19 or 0 on error
    dope_field_t fields[DOPE_INSTRUCTION_PARTS];     // 5
} dope_instruction_t;

typedef struct {
    int ip;             // instruction pointer
    dope_instruction_t* instructions;
    size_t size;
    size_t capacity;
} dope_program_t;

dope_program_t* dope_new_program(size_t line_count);

void dope_free_program(dope_program_t* program);

bool dope_is_truncated(dope_line_t* line);

void dope_consume_remaining(FILE* istream);

size_t dope_read_line(dope_line_t* line, FILE* istream);

size_t dope_instruction_tokenize(dope_line_t* line, char* tokens[]);

int dope_lookup_opcode(const char* mnemonic);

void dope_input_instruction(dope_instruction_t* instruction, FILE* istream);

void dope_print_line(dope_program_t* program, int line);

void dope_print_program(dope_progam_t* program);

#endif
