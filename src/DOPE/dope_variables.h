/**
 * For the purposes of DOPE a variable is a letter or a letter followed by a single digit.
 * For example:
 *  A, X, 25, QO, M, T7 are variables.
 *
 * @note There is an exception:
 * Do not use the letters L or O since these are indistinguishable from the
 * numbers 1 and 0 on a typewriter.
 *
 * There are also 4, 16-component vectors available in DOPE, denoted
 * by E, F, G, and H, followed by brackets.
 *
 */
#ifndef DOPE_VARIABLES_H
#define DOPE_VARIABLES_H

#include "dope_types.h"
#include <stdbool.h>

typedef enum {
    DOPE_NULL,
    DOPE_NUMBER,
    DOPE_VECTOR
} dope_var_type_t;

typedef union {
    dope_float_t number;
    dope_float_t* vector;
} dope_value_t;

typedef struct {
    dope_var_name_t name;
    dope_var_type_t type;
    dope_value_t value;
} dope_variable_t;

typedef struct {
    dope_variable_t* vars;
    dope_size_t size;
    dope_size_t capacity;
} dope_vartab_t;

dope_vartab_t* dope_new_vartab(dope_size_t capacity);

void dope_free_vartab(dope_vartab_t* vartab);

bool dope_is_valid_var_name(const char* name);

const dope_float_t* dope_const_pvar(const dope_vartab_t* vartab, const dope_var_name_t name);

dope_float_t* dope_pvar(dope_vartab_t* vartab, const dope_var_name_t name);

void dope_print_var(const dope_variable_t* var);

void dope_print_vartab(const dope_vartab_t* vartab);

#endif
