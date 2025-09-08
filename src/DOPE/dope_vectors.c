#include "dope_vectors.h"

// max 4 16-component vectors available E, F, G, and H
dope_vectab_t* dope_new_vectab() { }

void dope_free_vectab(dope_vectab_t* vectab){ }

dope_vector_t* dope_find_vec(dope_vectab_t* vectab, const char name) { }

dope_vector_t* dope_alloc_vec(dope_vectab_t* vectab, const char name) { }

//void dope_dealloc_vec(dope_vectab_t* vectab, const char name) { } //no scope in DOPE so redundant

void dope_set_val(dope_vectab_t* vectab, const char name, float value, dope_size_t i) { }

float dope_get_val(const dope_vectab_t* vectab, const char name, dope_size_t i) { }
