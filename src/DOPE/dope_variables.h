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

dope_var_t* dope_find_var(const dope_vartab_t* vartab, const dope_var_name_t name);

dope_var_t* dope_alloc_var(dope_vartab_t* vartab, const dope_var_name_t name);

//void dope_dealloc_var(dope_vartab_t* vartab, const dope_var_name_t name); //no scope in DOPE so redundant

void dope_set_var(dope_vartab_t* vartab, const dope_var_name_t name, float value);

float dope_get_var(const dope_vartab_t* vartab, const dope_var_name_t name);

#endif
