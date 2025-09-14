#include "dope_interpret.h"
#include "dope_constants.h"
#include "dope_data.h"
#include "dope_program.h"
#include "dope_types.h"
#include "dope_vectors.h"
#include <assert.h>
#include <inttypes.h>

dope_fn_t dispatch_table[] = {
    [DOPE_OP_ADD] = NULL,
    [DOPE_OP_SUB] = NULL,
    [DOPE_OP_MUL] = NULL,
    [DOPE_OP_DIV] = NULL,
    [DOPE_OP_STORE] = NULL,
    [DOPE_OP_SQR] = NULL,
    [DOPE_OP_EXP] = NULL,
    [DOPE_OP_LOG] = NULL,
    [DOPE_OP_SIN] = NULL,
    [DOPE_OP_COMPARE] = NULL,
    [DOPE_OP_GOTO] = dope_goto,
    [DOPE_OP_LABEL] = dope_print_label,
    [DOPE_OP_PRINT] = NULL,
    [DOPE_OP_NEWLN] = dope_println,
    [DOPE_OP_INPUT] = NULL,
    [DOPE_OP_LOOP] = NULL,
    [DOPE_OP_END] = NULL,
    [DOPE_OP_STOP] = dope_stop,
    [DOPE_OP_START] = dope_start
};

void dope_interpret(
    dope_size_t vartab_size,
    dope_program_t* program,
    dope_data_t* data
) {
    dope_vartab_t* vartab = dope_new_vartab(vartab_size);
    dope_vectab_t* vectab = dope_new_vectab();
    assert(vartab);
    assert(vectab);
    while(program->ip < program->size) {
        dope_fn_t fn = dispatch_table[dope_opcode(program)];
        fn(program, vartab, vectab, data);
    }
    dope_free_vectab(vectab);
    dope_free_vartab(vartab);
}

// 11. T - transfer execution to line number
void dope_goto(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data) {
    char* endptr = NULL;
    // dope_field_to_int(program, 1)
    // dope_field_to_float(program, 2)
    // dope_field_to_str(program, 3)
    program->ip = (dope_size_t)strtoimax(program->instructions[program->ip].fields[1], &endptr, 10) - 1;
}

// 12. A - Print label
void dope_print_label(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data) {
    printf("%s", (char*)dope_next_label(data));
    program->ip++;
}

// 14. N - Printer: Start new line
void dope_println(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data) {
    printf("\n>");
    program->ip++;
}

// 18. F - Stop! (To be used as final step for single data set)
void dope_stop(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data) {
    printf("\n>STOP\n");
    program->ip = program->size;
}

// 19. S - Start computing. Must be on bottom of all programs.
void dope_start(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data) {
    printf("\n>START\n>");
    program->ip = 0;
}
