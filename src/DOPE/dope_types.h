#ifndef DOPE_TYPES_H
#define DOPE_TYPES_H

#include "dope_constants.h"
#include <stdint.h>

typedef uint8_t dope_size_t;

typedef float dope_float_t;

typedef float dope_vector_t[DOPE_VECTOR_SIZE];

typedef char dope_line_t[DOPE_LINE_SIZE];

typedef char dope_field_t[DOPE_FIELD_SIZE];

typedef char dope_var_name_t[DOPE_VAR_NAME_SIZE];

#endif
