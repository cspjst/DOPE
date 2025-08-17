#ifndef DOPE_CONSTANTS_H
#define DOPE_CONSTANTS_H

#include <stdint.h>

#define DOPE_PROGRAM_LINES_MAX      99
#define DOPE_LINE_SIZE              40
#define DOPE_INSTRUCTION_SIZE       4
#define DOPE_INSTRUCTION_COUNT      19
#define DOPE_FIELD_SIZE             16
#define DOPE_DATA_SHEET_FIELDS      4


static const char* DOPE_INSTRUCTIONS[] = {
    "+", "-", ".", "/", ";", "SQR", "EXP", "LOG", "SIN",
    "C", "T", "A", "P", "N", "J", "Z", "E", "F", "S"
};

static const uint8_t DOPE_FEILDS[] = {
    3, 3, 3, 3, 2, 2, 2, 2, 2,
    5, 1, 0, 1, 0, 1, 3, 0, 0, 0
};

#endif
