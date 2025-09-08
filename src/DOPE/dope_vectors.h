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

dope_vector_t* dope_find_vector(dope_vectab_t* vectab, char name);

void dope_vector_set(dope_vector_t* v, dope_size_t i, float value);

float dope_vector_get(dope_vector_t* v, dope_size_t i);

#endif
