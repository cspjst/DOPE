/**
 * Arrays (vectors) did not have to be declared and had a default size (16).
 * There are 4 16-component vectors available in DOPE,
 * denoted by E, F, G, and H, followed by brackets.
 */
#ifndef DOPE_VECTORS_H
#define DOPE_VECTORS_H

#include "dope_constants.h"
#include "dope_errors.h"
#include "dope_types.h"
#include <stdint.h>

typedef struct {
    char name; // E, F, G or H
    dope_float_t vals[DOPE_VECTOR_SIZE];
    dope_error_t error_code;
} dope_vector_t;

typedef struct {
    dope_vector_t* vecs;
    dope_size_t size;
    dope_size_t capacity;
} dope_vectab_t;

dope_vectab_t* dope_new_vectab(); // max 4 vectors

void dope_free_vectab(dope_vectab_t* vectab);

dope_vector_t* dope_find_vec(dope_vectab_t* vectab, const char name);

dope_vector_t* dope_alloc_vec(dope_vectab_t* vectab, const char name);

//void dope_dealloc_vec(dope_vectab_t* vectab, const char name); //no scope in DOPE so redundant

// this is functions can just take float* agnostic to var_t or vec_t
float* dope_vec_pfloat(const dope_vectab_t* vectab, const char name, dope_size_t i);

#endif
