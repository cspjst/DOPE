#ifndef DOPE_INTERPRET_H
#define DOPE_INTERPRET_H

#include "dope_program.h"
#include "dope_data.h"
#include "dope_variables.h"
#include "dope_vectors.h"

typedef void (*dope_fn_t)(
    dope_program_t*,
    dope_vartab_t*,
    dope_vectab_t*,
    dope_data_t*
);

void dope_interpret(
    dope_size_t vartab_size,
    dope_program_t* program,
    dope_data_t* data
);

const dope_float_t dope_read_number(
    dope_size_t i,
    dope_program_t* program,
    dope_vartab_t* vars,
    dope_vectab_t* vecs
);

void dope_write_number(
    dope_float_t number,
    dope_size_t i,
    dope_program_t* program,
    dope_vartab_t* vars,
    dope_vectab_t* vecs
);

void dope_op_add(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_op_sub(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_op_mul(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_op_div(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_op_store(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_op_sqr(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_op_exp(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_op_log(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_sin(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_op_compare(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_op_goto(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_op_print_label(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_op_print(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_op_println(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_op_input(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_op_loop(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_op_end(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_op_stop(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_op_start(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

#endif
