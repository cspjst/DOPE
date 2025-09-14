#ifndef DOPE_INTERPRET_H
#define DOPE_INTERPRET_H

#include "dope_program.h"
#include "dope_data.h"
#include "dope_variables.h"
#include "dope_vectors.h"

typedef void (*dope_fn_t)(dope_size_t* ip, dope_vartab_t*, dope_vectab_t*, dope_data_t*);

void dope_interpret(
    dope_size_t vartab_size,
    dope_program_t* program,
    dope_data_t* data
);

void dope_stop(dope_size_t* ip, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

void dope_start(dope_size_t* ip, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data);

#endif
