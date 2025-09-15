#include "dope_errors.h"
#include <stdio.h>

const char* const DOPE_ERROR_MESSAGES[] = {
    "Success",                  // DOPE_ERR_SUCCESS
    "NULL pointer",             // DOPE_ERR_NULL
    "No input!",                // DOPE_ERR_NO_INPUT   EOF or error
    "No instruction!",          // DOPE_ERR_NO_INSTR    empty line
    "Invalid instruction!",     // DOPE_ERR_UNKNOWN_INSTR
    "Not enough operands!",     // DOPE_ERR_TOO_FEW_ARGS
    "Too many operands!",       // DOPE_ERR_TOO_MANY_ARGS
    "Input too long!",          // DOPE_ERR_LINE_TOO_LONG
    "Invalid char!",            // DOPE_ERR_INVALID_CHAR
    "Wrong number format!",     // DOPE_ERR_INVALID_NUMBER_FORMAT
    "Invalid character(s) in field!",   // DOPE_ERR_INVALID_FIELD
    "Number out of range!",     // DOPE_ERR_NUMBER_OUT_OF_RANGE
    "Missing stop code!",       // DOPE_ERR_MISSING_STOP_CODE
    "Variable name not found!", // DOPE_ERR_VAR_NOT_FOUND
    "Vector name not found!",   // DOPE_ERR_VEC_NOT_FOUND
    "Variable table full!",     // DOPE_ERR_OUT_OF_VARS
    "Type mismatch!",           // DOPE_ERR_TYPE_MISMATCH
    "Absent/malformed ending!"  // DOPE_ERR_FINISH
};

const char* dope_error_message(dope_error_t error_code) {
    return DOPE_ERROR_MESSAGES[error_code];
}

void dope_panic(uint8_t line, dope_error_t e, const char* info) {
    printf("ERROR input %d: %s %s\n", line, dope_error_message(e), info);
}
