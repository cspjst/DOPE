#include "dope_errors.h"
#include <stdio.h>

const char* const DOPE_ERROR_MESSAGES[] = {
    "Success",                  // DOPE_ERR_SUCCESS
    "NULL pointer",             // DOPE_ERR_NULL
    "No input!",                // DOPE_ERR_NO_INPUT   EOF or error
    "No instruction!",          // DOPE_ERR_NO_INSTR    empty line
    "Invalid instruction!",     // DOPE_ERR_UNKNOWN_INSTR
    "Not enough operands!",     // DOPE_ERR_TOO_FEW_ARGS,    // not enough operands
    "Too many operands!",       // DOPE_ERR_TOO_MANY_ARGS,   // too many operands
    "Input too long!",          // DOPE_ERR_LINE_TOO_LONG    // input line too long
    "Found a space at input!",  // DOPE_ERR_INVALID_CHAR
    "Wrong number format!",     // DOPE_ERR_INVALID_NUMBER_FORMAT
    "Exponent out of range!",   // DOPE_ERR_EXPONENT_OUT_OF_RANGE
    "Absent/malformed FINISH!"  // DOPE_ERR_FINISH
};

const char* dope_error_message(uint8_t error_code) {
    return DOPE_ERROR_MESSAGES[error_code];
}

void dope_panic(uint8_t line, dope_error_t e, char* info) {
    printf("ERROR Line %d: %s %s\n", line, dope_error_message(e), info);
}
