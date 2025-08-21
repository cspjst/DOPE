#include "dope_program.h"
#include "dope_constants.h"
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

dope_program_t* dope_new_program(size_t line_count) {
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
    return program;
}

void dope_free_program(dope_program_t* program) {
    if (program) {
        free(program->instructions);
        free(program);
    }
}

bool dope_is_truncated(dope_line_t* line) {
   if (!line) {
       return false;
   }
   size_t len = strlen(*line);
   // truncated if...
   return ((*line)[len - 1] != '\n') &&     // true no newline
          (len == DOPE_LINE_SIZE - 1);      // true buffer full
}

void dope_consume_remaining(FILE* istream) {
    int ch;
    while ((ch = fgetc(istream)) != '\n' && ch != EOF);
}

// line is ...\n\0 on success or ...\0 on truncation or \0 on fail
size_t dope_read_line(dope_line_t* line, FILE* istream) {
    if (!line || !istream) {
        (*line)[0] = '\0';  // "" on failure
        return 0;
    }
    if (!fgets(*line, DOPE_LINE_SIZE, istream)) {
        (*line)[0] = '\0';  // read fail or EOF
        return 0;
    }
    return strlen(*line);
}

size_t dope_instruction_tokenize(dope_line_t* line, char* tokens[]) {
    if (!line || !tokens) {
        return 0;
    }
    size_t count = 0;
    char* tok = strtok(*line, " \t\r");
    while (tok != NULL && count < DOPE_INSTRUCTION_PARTS) {
        tokens[count++] = tok;
        tok = strtok(NULL, " \t\r");
    }
    return count;
}

int dope_lookup_opcode(const char* mnemonic) { // just a simple linear search
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

// @note expects instruction->number to be pre-populated
void dope_input_token(dope_instruction_t* instruction, FILE* istream) {
    dope_line_t line;
    // 1. read the line
    size_t length = dope_read_line(&line, istream);
    if(dope_is_truncated(&line)) {
        instruction->opcode = 0;
        instruction-error_code = DOPE_ERR_LINE_TOO_LONG;
        dope_consume_remaining(istream);
        return;
    }
    // 2. trim the line
    line[strcspn(line, "\n")] = '\0';
    // 3. tokenize the line
    size_t token_count = dope_instruction_tokenize(&line, instruction->fields);
    if (token_count == 0) {
        instruction->opcode = 0;
        instruction-error_code = DOPE_ERR_NO_INSTR;
        return;
    }
    // 4. look up the opcode
    instruction->opcode = dope_lookup_opcode(instruction->fields[0]);
    if(instruction->opcode == 0) {
        instruction-error_code = DOPE_ERR_UNKNOWN_INSTR;
        return;
    }
    // 5. check number of operands 
    if(token_count - 1 < DOPE_OPERAND_COUNT[instruction->opcode - 1]) {
        instruction->opcode = 0;
        instruction-error_code = DOPE_ERR_TOO_FEW_ARGS;
        return;
    }
    if(token_count - 1 > DOPE_OPERAND_COUNT[instruction->opcode - 1]) {
        instruction->opcode = 0;
        instruction->error_code = DOPE_ERR_TOO_MANY_ARGS;
        return;
    }
    // 6. recognized instruction and correct number of operands 
}

void dope_print_instruction(dope_instruction_t* instruction) {
    printf("%i %s %s %s %s %s\n", 
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
        dope_print_instruction(program[i]);
    }
}
