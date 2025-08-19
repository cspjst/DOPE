#include "dope_program.h"

dope_program_t* dope_new_program(size_t line_count) {
    dope_program_t* program = malloc(sizeof(dope_data_sheet_t));
    if (!program) {
        return NULL;
    }

    program->tokens = calloc(line_count, sizeof(dope_token_t));
    if (!program->tokens) {
        free(tokens);
        return NULL;
    }

    program->capacity = line_count;
    program->size = 0;
    return program;
}

void dope_free_program(dope_program_t* program) {
    if (program) {
        free(program->tokens);
        free(program);
    }
}

void dope_input_token(dope_token_t* token, FILE* istream) {
    dope_line_t buffer;
    char* tokens[DOPE_INSTRUCTION_FIELDS + 1];  // array of strings for strtok
    int token_count = 0;
    token->instr = 0; 
    if (fgets(buffer, sizeof(buffer), istream) == NULL) { 
        token->line = DOPE_ERR_NO_INPUT;
        return;
    } 
    int buflen = strlen(buffer);
    if (buflen == DOPE_LINE_SIZE - 1 && buffer[buflen - 1] != '\n') {  // Check for truncation
        int ch;
        while ((ch = fgetc(istream)) != '\n' && ch != EOF); // Line too long — consume rest of line
        token->line = DOPE_ERR_LINE_TOO_LONG;
        return;
    }
    if (buflen > 0 && buffer[buflen - 1] == '\n') {  // Strip fgets newline
        buffer[buflen - 1] = '\0';
        buflen--;
    }
    char* tok = strtok(buffer, " \t\r"); // tokenize by white space
    while (tok != NULL && token_count < DOPE_INSTRUCTION_FIELDS + 1) {
        tokens[token_count++] = tok;
        tok = strtok(NULL, " \t\r");
    }
    if (token_count == 0) {
        token->line = DOPE_ERR_NO_INSTR;
        return;
    }
    // linear search for instruction 
    for (int i = 0; i < 19; i++) {
        if (strcmp(tokens[0], DOPE_INSTRUCTIONS[i]) == 0) {
            uint8_t expected = DOPE_FEILDS[i];
            uint8_t available = token_count - 1;
            if (available < expected) {
                token->instr = 0;
                token->line = DOPE_ERR_TOO_FEW_ARGS;
                return;
            }
            token->instr = (uint8_t)(i + 1);  // Success 
            for (int j = 0; j < expected && j < DOPE_INSTRUCTION_FIELDS; j++) { // Copy operands
                int copy_len = (int)strlen(tokens[j + 1]);
                if (copy_len >= DOPE_FIELD_SIZE) {
                    copy_len = DOPE_FIELD_SIZE - 1;
                }
                memcpy(token->fields[j], tokens[j + 1], copy_len);
                token->fields[j][copy_len] = '\0';
            }
            return;
        }
    }
    token->instr = 0;
    token->line = DOPE_ERR_UNKNOWN_INSTR;
}
