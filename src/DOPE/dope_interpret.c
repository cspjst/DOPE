#include "dope_interpret.h"
#include "dope_constants.h"
#include "dope_data.h"
#include "dope_errors.h"
#include "dope_program.h"
#include "dope_types.h"
#include "dope_utility.h"
#include "dope_variables.h"
#include "dope_vectors.h"
#include <assert.h>


dope_fn_t dispatch_table[] = {
    [DOPE_OP_ADD] = dope_add,
    [DOPE_OP_SUB] = NULL,
    [DOPE_OP_MUL] = NULL,
    [DOPE_OP_DIV] = NULL,
    [DOPE_OP_STORE] = dope_store,
    [DOPE_OP_SQR] = NULL,
    [DOPE_OP_EXP] = NULL,
    [DOPE_OP_LOG] = NULL,
    [DOPE_OP_SIN] = NULL,
    [DOPE_OP_COMPARE] = NULL,
    [DOPE_OP_GOTO] = dope_goto,
    [DOPE_OP_LABEL] = dope_print_label,
    [DOPE_OP_PRINT] = dope_print,
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

const dope_float_t dope_read_number(dope_size_t field, dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs) {
    const char* name = dope_field_to_str(program, field);
    if(dope_is_number(name)) {
        return dope_field_to_constant(program, field);
    }
    if(dope_is_valid_var_name(name)) {
        return *dope_const_pvar(vars, name);
    }
    //if(dope_is_valid_vec_name(name))...
    dope_panic(program->ip + 1, DOPE_ERR_INVALID_FIELD, name);
    return 0.0f;
}

void dope_write_number(dope_float_t number, dope_size_t field, dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs) {
    const char* name = dope_field_to_str(program, field);
    if(dope_is_valid_var_name(name)) {
        *dope_pvar(vars, name) = number;
        return;
    }
    //if(dope_is_valid_vec_name(name))...
    dope_panic(program->ip + 1, DOPE_ERR_INVALID_FIELD, name);
    return;
}

// 1. + - A + B -> C
void dope_add(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data) {
    const dope_float_t a = dope_read_number(1, program, vars, vecs);
    const dope_float_t b = dope_read_number(2, program, vars, vecs);
    dope_write_number(a + b, 3, program, vars, vecs);
    program->ip++;
}

// 5. ; - A -> B
void dope_store(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data) {
    const dope_float_t a = dope_read_number(1, program, vars, vecs);
    dope_write_number(a, 2, program, vars, vecs);
    program->ip++;
}

// 11. T - transfer execution to line number
void dope_goto(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data) {
    program->ip = dope_field_to_line_number(program, 1) - 1;    // retrieve the line number from current ip instruction's 2nd field and zero adjust
}

// 12. A - Print label
void dope_print_label(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data) {
    printf("%s", (char*)dope_next_label(data));
    program->ip++;
}

// 13. P - Print number
void dope_print(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data) {
    printf("%f\t", dope_read_number(1, program, vars, vecs));
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
