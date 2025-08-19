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

}
