#ifndef DOPE_ERRORS_H
#define DOPE_ERRORS_H

#include <stdint.h>

extern const char* const DOPE_ERROR_MESSAGES[];

typedef enum {
    DOPE_ERR_SUCCESS = 0,
    DOPE_ERR_NULL,
    DOPE_ERR_NO_INPUT,        // EOF
    DOPE_ERR_NO_INSTR,        // empty line
    DOPE_ERR_UNKNOWN_INSTR,   // invalid instruction
    DOPE_ERR_TOO_FEW_ARGS,    // not enough operands
    DOPE_ERR_TOO_MANY_ARGS,   // too many operands
    DOPE_ERR_LINE_TOO_LONG,   // input line too long
    DOPE_ERR_INVALID_CHAR,    // found a space at input
    DOPE_ERR_INVALID_NUMBER_FORMAT, // does not meet DOPE format
    DOPE_ERR_EXPONENT_OUT_OF_RANGE, // -36 < e > 36
    DOPE_ERR_MISSING_STOP_CODE,     // exoected ' not found 
    DOPE_ERR_FINISH           // absent or malformed
} dope_error_t;

const char* dope_error_message(uint8_t error_code);

void dope_panic(uint8_t line, dope_error_t e, char* info);

#endif
