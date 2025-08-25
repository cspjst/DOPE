/**
 * @file dope_program.h
 * @brief DOPE Interpreter: Program structure and input pipeline
 * @version 0.1
 * @date 2025-08-24
 * @details
 * This header defines the core program structure and input functions for the
 * Dartmouth Oversimplified Programming Experiment (DOPE)
 * An Historical Re-creation in C interpreter.
 *
 * It provides:
 * - Instruction and program data structures
 * - Line-by-line input with error recovery
 * - Tokenization and opcode resolution
 * - Stream synchronization on truncated lines
 * - Integration with error reporting and printing
 */
#ifndef DOPE_PROGRAM_H
#define DOPE_PROGRAM_H

#include "dope_constants.h"
#include "dope_types.h"
#include "dope_errors.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Null-terminated array of valid instruction mnemonics.
 * @details
 * Indexed 0-based; corresponds to 1-based opcodes returned by
 * dope_lookup_opcode(). Order must match DOPE_OPERAND_COUNT.
 */
extern const char* const DOPE_INSTRUCTIONS[];

/**
 * @brief Array of operand counts for each instruction.
 * @details
 * DOPE_OPERAND_COUNT[i] = number of operands expected by DOPE_INSTRUCTIONS[i].
 * Used during instruction validation.
 */
extern const uint8_t DOPE_OPERAND_COUNT[];

/**
 * @brief Fixed-size record for holding tokenized instruction parts.
 * @details
 * Represents one parsed line: up to DOPE_INSTRUCTION_PARTS tokens,
 * each of size DOPE_FIELD_SIZE. Used as scratch space during input.
 */
typedef dope_field_t dope_instruction_record_t[DOPE_INSTRUCTION_PARTS];

/**
 * @brief Single parsed instruction with source and error context.
 * @details
 * Holds the result of parsing one source line. Includes:
 * - line_number: source line (1-based)
 * - error_code: set if opcode == 0
 * - opcode: 1–19 for valid, 0 for error
 * - fields: tokenized strings (fields[0] = opcode string)
 */
typedef struct {
    uint8_t line_number;           /**< Source line number (1–99) */
    uint8_t error_code;            /**< Error code if opcode == 0 */
    uint8_t opcode;                /**< 1–19 = valid opcode, 0 = error */
    dope_instruction_record_t fields; /**< Tokenized instruction parts */
} dope_instruction_t;

/**
 * @brief Dynamic array of instructions (program buffer).
 * @details
 * Represents a loaded DOPE program. Instructions are stored contiguously.
 * The input phase stops when an 'S' instruction is encountered.
 */
typedef struct {
    uint8_t ip;                        /**< Instruction pointer (index) */
    dope_instruction_t* instructions; /**< Owned array of instructions */
    uint8_t size;                   /**< Number of valid instructions */
    uint8_t capacity;               /**< Allocated instruction count */
} dope_program_t;

/**
 * @brief Create a new program buffer.
 * @param line_count Maximum number of instructions (capacity)
 * @return Pointer to new program, or NULL on allocation failure
 * @note Caller must free with dope_free_program()
 */
dope_program_t* dope_new_program(uint8_t line_count);

/**
 * @brief Free program and its instruction array.
 * @param program Pointer to program (may be NULL)
 */
void dope_free_program(dope_program_t* program);

/**
 * @brief Tokenize a line into fixed-size fields.
 * @param line Input line (modified in place)
 * @param tokens Output array of string fields
 * @return Number of tokens extracted (0 to DOPE_INSTRUCTION_PARTS)
 * @details
 * Uses strtok to split on whitespace. Each token is copied
 * safely into tokens[i] with null termination.
 */
dope_size_t dope_instruction_tokenize(dope_line_t* line, dope_field_t tokens[]);

/**
 * @brief Look up opcode by mnemonic string.
 * @param mnemonic Null-terminated instruction name
 * @return 1-based opcode (1–19) on match, 0 if not found or invalid
 * @details
 * Performs linear search of DOPE_INSTRUCTIONS. Returns 0 for
 * NULL, empty, or unknown mnemonics.
 */
dope_size_t dope_lookup_opcode(const char* mnemonic);

/**
 * @brief Clear instruction fields (token storage only).
 * @param instruction Pointer to instruction
 * @details
 * Zeroes the fields array to prevent carryover from previous use.
 * Does not clear line_number, opcode, or error_code.
 */
void dope_clear_instruction(dope_instruction_t* instruction);

/**
 * @brief Parse a single instruction from input stream.
 * @param instruction Output instruction (must be non-null)
 * @param istream Input stream
 * @details
 * Reads and parses one line. Sets opcode and error_code.
 * Stores original tokens in fields for error reporting.
 * Preserves instruction->line_number.
 */
void dope_input_instruction(dope_instruction_t* instruction, FILE* istream);

/**
 * @brief Load a program from input stream.
 * @param program Target program buffer
 * @param stream Input stream
 * @details
 * Reads lines until EOF, capacity reached, or 'S' instruction.
 * Validates each instruction and reports errors via printf.
 * Stops immediately after storing 'S'.
 */
void dope_input_program(dope_program_t* program, FILE* stream);

/**
 * @brief Print a single instruction in human-readable form.
 * @param instruction Pointer to instruction
 */
void dope_print_instruction(dope_instruction_t* instruction);

/**
 * @brief Print all instructions in a program.
 * @param program Pointer to program
 */
void dope_print_program(dope_program_t* program);

#endif /* DOPE_PROGRAM_H */
