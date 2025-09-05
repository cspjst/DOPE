#ifndef DOPE_CONSTANTS_H
#define DOPE_CONSTANTS_H

#define DOPE_STOP '\''           /**< Page 13 DOPE teaching notes 1962 "stop code"*/
#define DOPE_STOP_STR "'"       /**< As string for strtok */

#define DOPE_PROGRAM_LINES_MAX     99  /**< Max number of source lines in program (1–99) */
#define DOPE_LINE_SIZE             40  /**< Max length of input line including '\0' */
#define DOPE_INSTRUCTION_PARTS      6  /**< Max tokens per line: 1 opcode + 5 operands */
#define DOPE_FIELD_SIZE            12  /**< Max length of each operand string (e.g. "SQR", "-1111'11-11'") */
#define DOPE_OPERANDS_MAX           5  /**< Max number of operands an instruction can take */
#define DOPE_INSTRUCTION_COUNT     19  /**< Total number of valid opcodes in DOPE language */

typedef enum {
    DOPE_OP_INVALID = 0,

    DOPE_OP_ADD,        // 1  "+"
    DOPE_OP_SUB,        // 2  "-"
    DOPE_OP_MUL,        // 3  "."
    DOPE_OP_DIV,        // 4  "/"
    DOPE_OP_STORE,      // 5  ";"
    DOPE_OP_SQR,        // 6  "SQR"
    DOPE_OP_EXP,        // 7  "EXP"
    DOPE_OP_LOG,        // 8  "LOG"
    DOPE_OP_SIN,        // 9  "SIN"
    DOPE_OP_COMPARE,    // 10 "C"
    DOPE_OP_GOTO,       // 11 "T"
    DOPE_OP_LABEL,      // 12 "A"
    DOPE_OP_PRINT,      // 13 "P"
    DOPE_OP_NEWLN,      // 14 "N"
    DOPE_OP_INPUT,      // 15 "J"
    DOPE_OP_LOOP,       // 16 "Z"
    DOPE_OP_END,        // 17 "E"
    DOPE_OP_STOP,       // 18 "F"
    DOPE_OP_START       // 19 "S"
} dope_opcode_t;

#endif
