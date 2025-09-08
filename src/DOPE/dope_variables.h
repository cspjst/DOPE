/**
 * For the purposes of DOPE a variable is a letter ora letter followed by a single digit.
 * For example:
 *  A, X, 25, QO, M, T7 are variables.
 *
 * @note There is an exception:
 * Do not use the letters L or O since these are indistinguishable from the
 * numbers 1 and 0 on a typewriter.
 */
#ifndef DOPE_VARIABLES_H
#define DOPE_VARIABLES_H

#include "dope_constants.h"
#include "dope_errors.h"
#include "dope_types.h"

typedef char dope_var_name_t[DOPE_VAR_NAME_SIZE];

typedef struct {
    dope_var_name_t name;
    dope_float_t value;
    dope_error_t error_code;
} dope_var_t;

typedef struct {
    dope_var_t* vars;
    dope_size_t size;
    dope_size_t capacity;
} dope_vartab_t;

dope_vartab_t* dope_new_vartab(dope_size_t capacity);

void dope_free_vartab(dope_vartab_t* vartab);

dope_var_t* dope_alloc_var(dope_vartab_t* vartab, const char* name);

dope_var_t* dope_find_var(dope_vartab_t* vartab, dope_var_name_t name);

void dope_var_set(dope_var_t* v, float value);

float dope_var_get(dope_var_t* v);

#endif
