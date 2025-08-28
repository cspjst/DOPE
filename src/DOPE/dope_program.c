#include "dope_program.h"
#include "dope_constants.h"
#include "dope_errors.h"
#include "dope_types.h"
#include "dope_utility.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const char* const DOPE_INSTRUCTIONS[] = {
    "+", "-", ".", "/", ";", "SQR", "EXP", "LOG", "SIN",
    "C", "T", "A", "P", "N", "J", "Z", "E", "F", "S"
};

const uint8_t DOPE_OPERAND_COUNT[] = {
    3, 3, 3, 3, 2, 2, 2, 2, 2,
    5, 1, 0, 1, 0, 1, 3, 0, 0, 0
};

dope_program_t* dope_new_program(uint8_t line_count) {
    dope_program_t* program = malloc(sizeof(dope_program_t));
    if (!program) {
        return NULL;
    }

    program->instructions = calloc(line_count, sizeof(dope_instruction_t));
    if (!program->instructions) {
        free(program);
        return NULL;
    }

    program->capacity = line_count;
    program->size = 0;
    program->ip = 0;
    return program;
}

void dope_free_program(dope_program_t* program) {
    if (program) {
        free(program->instructions);
        free(program);
    }
}

dope_size_t dope_instruction_tokenize(dope_line_t* line, dope_instruction_record_t tokens) {
    if (!line || !tokens) {
        return 0;
    }
    uint8_t count = 0;
    // 1. Begin tokenization: extract first token using strtok
    //    strtok modifies *line, replacing delimiters with '\0'
    char* tok = strtok(*line, DOPE_DELIM_STR);
    // 2. Loop: while tokens exist and space remains
    while (tok != NULL && count < DOPE_INSTRUCTION_PARTS) {
        // 3. Measure token length and clamp to field size
        uint8_t len = strlen(tok);
        if (len >= DOPE_FIELD_SIZE) {
            len = DOPE_FIELD_SIZE - 1;  // Leave room for '\0'
        }
        // 4. Copy token safely into current field
        memcpy(tokens[count], tok, len);
        tokens[count][len] = '\0';  // Ensure null termination
        // 5. Advance to next token and field
        count++;
        tok = strtok(NULL, DOPE_DELIM_STR);  // Continue from where previous left off
    }
    return count;
}

dope_size_t dope_lookup_opcode(const char* mnemonic) { // just a simple linear search
    if (!mnemonic || !*mnemonic) {
        return 0;
    }
    for(int i = 0; i < DOPE_INSTRUCTION_COUNT; ++i) { // DOPE only has 19 opcodes
        if (strcmp(mnemonic, DOPE_INSTRUCTIONS[i]) == 0) {
            return i + 1;
        }
    }
    return 0;
}

void dope_clear_instruction(dope_instruction_t* instruction) {
    memset(instruction, 0, sizeof(dope_instruction_t));
}

// @note expects instruction->number to be pre-populated
void dope_input_instruction(dope_instruction_t* instruction, FILE* istream) {
    // 0. clear the instruction fields
    memset(instruction->fields, 0, sizeof(dope_instruction_record_t));
    // 1. read the line and cathc truncated and invalid character errors 
    dope_line_t line;
    uint8_t length = dope_read_line(&line, istream);
    if(dope_is_truncated(&line)) {
        instruction->opcode = DOPE_OP_INVALID;
        instruction->error_code = DOPE_ERR_LINE_TOO_LONG;
        dope_consume_remaining(istream);
        return;
    }
    if (dope_has_space(&line)) {
        instruction->opcode =DOPE_OP_INVALID;
        instruction->error_code = DOPE_ERR_INVALID_CHAR;
        return;
    }
    // 2. trim the line
    line[strcspn(line, "\n")] = '\0';
    // 3. tokenize the line
    uint8_t token_count = dope_instruction_tokenize(&line, instruction->fields);
    if (token_count == 0) {
        instruction->opcode = DOPE_OP_INVALID;
        instruction->error_code = DOPE_ERR_NO_INSTR;
        return;
    }
    // 4. look up the opcode
    instruction->opcode = dope_lookup_opcode(instruction->fields[0]);
    if(instruction->opcode == 0) {
        instruction->error_code = DOPE_ERR_UNKNOWN_INSTR;
        return;
    }
    // 5. check number of operands
    if(token_count - 1 < DOPE_OPERAND_COUNT[instruction->opcode - 1]) {
        instruction->opcode = DOPE_OP_INVALID;
        instruction->error_code = DOPE_ERR_TOO_FEW_ARGS;
        return;
    }
    if(token_count - 1 > DOPE_OPERAND_COUNT[instruction->opcode - 1]) {
        instruction->opcode = DOPE_OP_INVALID;
        instruction->error_code = DOPE_ERR_TOO_MANY_ARGS;
        return;
    }
    // 6. recognized instruction and correct number of operands
}

void dope_input_program(dope_program_t* program, FILE* stream) {
    if (!program || !stream) {
        return;
    }
    program->size = 0;
    dope_instruction_t instruction;

    while (program->size < program->capacity) {
        // 1. Parse next instruction
        dope_input_instruction(&instruction, stream);
        // 2. Store instruction (valid or invalid)
        program->instructions[program->size++] = instruction;
        // 3. EOF: stop cleanly
        if (instruction.opcode == DOPE_OP_INVALID && instruction.error_code == DOPE_ERR_NO_INPUT) {
            dope_panic(program->size, instruction.error_code, "");
            break;
        }
        // 4. Print error if invalid
        if (instruction.opcode == DOPE_OP_INVALID) {
            // 4.1 For certain errors, include context
            if (instruction.error_code == DOPE_ERR_UNKNOWN_INSTR ||
                instruction.error_code == DOPE_ERR_TOO_FEW_ARGS ||
                instruction.error_code == DOPE_ERR_TOO_MANY_ARGS) {
                dope_panic(program->size, instruction.error_code, instruction.fields[0]);
            }
            else {
                dope_panic(program->size, instruction.error_code, "");
            }
        }
        // 5. Stop on 'S' instruction (opcode 19)
        if (instruction.opcode == DOPE_OP_S) {  // 'S' = Stop
            break;
        }
    }
}

void dope_print_instruction(dope_instruction_t* instruction) {
    printf("%s %s %s %s %s\n",
        instruction->fields[0],
        instruction->fields[1],
        instruction->fields[2],
        instruction->fields[3],
        instruction->fields[4]
    );
    if(instruction->opcode == 0) {
        printf("ERROR %s\n", dope_error_message(instruction->error_code));
    }
}

void dope_print_program(dope_program_t* program) {
   for(int i = 0; i < program->size; i++) {
       printf("%i ", i + 1); // line number
       dope_print_instruction(&program->instructions[i]);
    }
}
