#ifndef DOPE_CONSTANTS_H
#define DOPE_CONSTANTS_H

#define DOPE_DELIM '\''          /**< Program parts and data parts delimiter pg 13 DOPE teaching notes 1962*/
#define DOPE_DELIM_STR "'"       /**< As string for strtok */

#define DOPE_PROGRAM_LINES_MAX     99  /**< Max number of source lines in program (1–99) */
#define DOPE_LINE_SIZE             40  /**< Max length of input line including '\0' */
#define DOPE_INSTRUCTION_PARTS      6  /**< Max tokens per line: 1 opcode + 5 operands */
#define DOPE_FIELD_SIZE            10  /**< Max length of each operand string (e.g. "X", "13.5") */
#define DOPE_OPERANDS_MAX           5  /**< Max number of operands an instruction can take */
#define DOPE_INSTRUCTION_COUNT     19  /**< Total number of valid opcodes in DOPE language */

#define DOPE_DATA_STRING_SIZE      20

typedef enum {
    DOPE_OP_INVALID = 0,

    DOPE_OP_ADD,        // 1  "+"
    DOPE_OP_SUB,        // 2  "-"
    DOPE_OP_MUL,        // 3  "."
    DOPE_OP_DIV,        // 4  "/"
    DOPE_OP_STOP_LINE,  // 5  ";"
    DOPE_OP_SQR,        // 6  "SQR"
    DOPE_OP_EXP,        // 7  "EXP"
    DOPE_OP_LOG,        // 8  "LOG"
    DOPE_OP_SIN,        // 9  "SIN"
    DOPE_OP_C,          // 10 "C"
    DOPE_OP_T,          // 11 "T"
    DOPE_OP_A,          // 12 "A"
    DOPE_OP_P,          // 13 "P"
    DOPE_OP_N,          // 14 "N"
    DOPE_OP_J,          // 15 "J"
    DOPE_OP_Z,          // 16 "Z"
    DOPE_OP_E,          // 17 "E"
    DOPE_OP_F,          // 18 "F"
    DOPE_OP_S           // 19 "S"
} dope_opcode_t;

#endif
