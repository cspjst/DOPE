#ifndef DOPE_OPERAND_H
#define DOPE_OPERAND_H

#include "dope_types.h"

typedef enum {
    DOPE_OP_NUMBER,
    DOPE_OP_LINE,
    DOPE_OP_VECTOR
} dope_op_type_t;

typedef union {
    dope_float_t number;
    dope_size_t line;
    dope_vector_t* vector;
} dope_value_t;

typedef struct {
    dope_var_name_t name;
    dope_op_type_t type;
    dope_value_t value;
} dope_operand_t;

#endif
