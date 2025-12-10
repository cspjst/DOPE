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
    program->ip = 0;
    program->capacity = line_count;
    program->size = 0;
    return program;
}

void dope_free_program(dope_program_t* program) {
    if (program) {
        free(program->instructions);
        free(program);
    }
}

void dope_clear_instruction(dope_instruction_t* instruction) {
    memset(instruction, 0, sizeof(dope_instruction_t));
}

dope_size_t dope_instruction_tokenize(dope_line_t* line, dope_instruction_record_t tokens) {
    if (!line || !tokens) {
        return 0;
    }
    uint8_t count = 0;
    // 1. Begin tokenization: extract first token using strtok
    //    strtok modifies *line, replacing delimiters with '\0'
    char* tok = strtok(*line, DOPE_STOP_STR);
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
        tok = strtok(NULL, DOPE_STOP_STR);  // Continue from where previous left off
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

void dope_input_instruction(dope_instruction_t* instruction, FILE* istream) {
    dope_clear_instruction(instruction);
    instruction->opcode = DOPE_OP_INVALID; // default to error
    // 1. read the line and catch truncated and invalid character errors
    dope_line_t line;
    uint8_t length = dope_read_line(&line, istream);
    if(length == 0) {
        instruction->error_code = DOPE_ERR_NO_INPUT;
        return;
    }
    if(dope_is_truncated(&line)) {
        instruction->error_code = DOPE_ERR_LINE_TOO_LONG;
        strncpy((char*)&instruction->fields[0], (char*)&line, DOPE_LINE_SIZE);
        dope_consume_remaining(istream);
        return;
    }
    // trim line
    line[strcspn(line, "\n")] = '\0';
    // 2. missing stop code check
    if(line[length - 2] != '\'') {
        instruction->error_code = DOPE_ERR_MISSING_STOP_CODE;
        strncpy((char*)&instruction->fields[0], (char*)&line, length);
        return;
    }
    // 3. invalid character check
    if (dope_has_space((char*)&line)) {
        instruction->error_code = DOPE_ERR_INVALID_CHAR;
        strncpy((char*)&instruction->fields[0], (char*)&line, length);
        return;
    }
    // 4. uppercase
    dope_string_toupper((char*)&line);
    // 5. tokenize the line
    uint8_t token_count = dope_instruction_tokenize(&line, instruction->fields);
    if (token_count == 0) {
        instruction->error_code = DOPE_ERR_NO_INSTR;
        return;
    }
    // 6. look up the opcode
    instruction->opcode = dope_lookup_opcode(instruction->fields[0]);
    if(instruction->opcode == 0) {
        instruction->error_code = DOPE_ERR_UNKNOWN_INSTR;
        strncpy((char*)&instruction->fields[0], (char*)&line, length);
        return;
    }
    // 7. check number of operands
    if(token_count - 1 < DOPE_OPERAND_COUNT[instruction->opcode - 1]) {
        instruction->opcode = DOPE_OP_INVALID;
        instruction->error_code = DOPE_ERR_TOO_FEW_ARGS;
        strncpy((char*)&instruction->fields[0], (char*)&line, length);
        return;
    }
    if(token_count - 1 > DOPE_OPERAND_COUNT[instruction->opcode - 1]) {
        instruction->opcode = DOPE_OP_INVALID;
        instruction->error_code = DOPE_ERR_TOO_MANY_ARGS;
        strncpy((char*)&instruction->fields[0], (char*)&line, length);
        return;
    }
    // 8. recognized instruction and correct number of operands
    instruction->error_code = DOPE_ERR_SUCCESS;
}

void dope_input_program(dope_program_t* program, FILE* istream) {
    if (!program || !istream) {
        dope_panic(0, DOPE_ERR_NO_INPUT, "NULL program or file");
        return;
    }
    program->size = 0;
    while (program->size < program->capacity) {
        printf("%i ", program->size + 1);
        // 1. parse next instruction
        dope_input_instruction(&program->instructions[program->size], istream);
        // 2. no input (EOF)
        if (program->instructions[program->size].error_code == DOPE_ERR_NO_INPUT) {
            dope_panic(program->size, program->instructions[program->size].error_code, "EOF without 'F'");
            return;
        }
        // 3. error exit
        if (program->instructions[program->size].opcode == DOPE_OP_INVALID) {
                dope_panic(
                    program->size + 1,
                    program->instructions[program->size].error_code,
                    program->instructions[program->size].fields[0]
                );
                if(istream == stdin) continue;
                else return;
        }
        // 4. stop on 'S' instruction (opcode 19)
        if (program->instructions[program->size].opcode == DOPE_OP_START) {
            if(program->instructions[program->size - 1].opcode == DOPE_OP_STOP) {
                program->ip = program->size;
                program->size++;
                return;
            }
            else {
                dope_panic(program->size, DOPE_ERR_FINISH, "S but no preceding F!");
                if(istream == stdin) continue;
                else return;
            }
        }
        // 5. valid argument
        program->size++;
    }
    dope_panic(program->size, DOPE_ERR_FINISH, "Program exceeds capacity");
}

dope_opcode_t dope_opcode(dope_program_t* program) {
    return program->instructions[program->ip].opcode;
}

const dope_size_t dope_field_to_line_number(const dope_program_t* program, int i) {
    char* field = program->instructions[program->ip].fields[i];
    char *endptr;
    return (dope_size_t)strtoul(field, &endptr, DOPE_BASE_10);
}

const dope_float_t dope_field_to_constant(const dope_program_t* program, int i) {
    char* field = program->instructions[program->ip].fields[i];
    char* endptr;
    return (dope_float_t)strtod(field, &endptr);
}

const char* dope_field_to_str(const dope_program_t* program, int i) {
    return program->instructions[program->ip].fields[i];
}

void dope_print_instruction(const dope_instruction_t* instruction, FILE* ostream) {
    fprintf(ostream, "%s%c", instruction->fields[0], DOPE_STOP);
    for(int i = 0; i <  DOPE_OPERAND_COUNT[instruction->opcode]; ++i) { 
        fprintf(ostream, "%s%c", instruction->fields[i + 1], DOPE_STOP);
    }
}

void dope_print_program(const dope_program_t* program, FILE* ostream) {
   for(int i = 0; i < program->size; i++) {
       fprintf(ostream, "%i ", i + 1); // line number
       dope_print_instruction(&program->instructions[i], ostream);
   }
}
