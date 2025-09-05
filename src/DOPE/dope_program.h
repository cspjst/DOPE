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
    uint8_t opcode;                /**< 1–19 = valid opcode, 0 = error */
    uint8_t error_code;            /**< Error code if opcode == 0 */
    dope_instruction_record_t fields; /**< Tokenized instruction parts */
} dope_instruction_t;

typedef struct {
    uint8_t ip;                        /**< Instruction pointer (index) */
    dope_instruction_t* instructions; /**< Owned array of instructions */
    uint8_t size;                   /**< Number of valid instructions */
    uint8_t capacity;               /**< Allocated instruction count */
} dope_program_t;

dope_program_t* dope_new_program(uint8_t line_count);

void dope_free_program(dope_program_t* program);

void dope_clear_instruction(dope_instruction_t* instruction);

dope_size_t dope_instruction_tokenize(dope_line_t* line, dope_field_t tokens[]);

dope_size_t dope_lookup_opcode(const char* mnemonic);

void dope_input_instruction(dope_instruction_t* instruction, FILE* istream);

void dope_input_program(dope_program_t* program, FILE* stream);

void dope_print_instruction(dope_instruction_t* instruction);

void dope_print_program(dope_program_t* program);

#endif
