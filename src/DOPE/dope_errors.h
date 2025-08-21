#ifndef DOPE_ERRORS_H
#define DOPE_ERRORS_H

#include <stdint.h>

extern const char* const DOPE_ERROR_MESSAGES[];

typedef enum {
    DOPE_ERR_SUCCESS = 0,
    DOPE_ERR_NO_INPUT,        // EOF
    DOPE_ERR_NO_INSTR,        // empty line
    DOPE_ERR_UNKNOWN_INSTR,   // invalid instruction
    DOPE_ERR_TOO_FEW_ARGS,    // not enough operands
    DOPE_ERR_TOO_MANY_ARGS,   // too many operands
    DOPE_ERR_LINE_TOO_LONG    // input line too long
} dope_error_t;

void dope_error_message(uint8_t error_code);

#endif
