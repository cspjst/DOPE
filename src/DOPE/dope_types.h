#ifndef DOPE_TYPES_H
#define DOPE_TYPES_H

#include "dope_constants.h"

typedef char dope_line_t[DOPE_LINE_SIZE];

typedef dope_line_t dope_program_t[DOPE_PROGRAM_LINES_MAX];

typedef char dope_instruction_t[DOPE_INSTRUCTION_SIZE];

#endif
