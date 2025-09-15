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

void dope_add(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_sub(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_mul(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_div(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_store(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_sqr(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_exp(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_log(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_sin(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_compare(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_goto(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_print_label(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_print(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_println(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_input(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_loop(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_end(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_stop(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_start(dope_program_t* program, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

#endif
