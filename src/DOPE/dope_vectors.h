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
    dope_vector_t vectors[DOPE_VECTORS_MAX];
    dope_size_t size;
    dope_size_t capacity;
} dope_vectab_t;

dope_vectab_t* dope_new_vectab(); // fixed 4 vectors

void dope_free_vectab(dope_vectab_t* vectab);

#endif
