#ifndef DOPE_CONSTANTS_H
#define DOPE_CONSTANTS_H

#define DOPE_PROGRAM_LINES_MAX     99  /**< Max number of source lines in program (1–99) */
#define DOPE_LINE_SIZE             40  /**< Max length of input line including '\0' */
#define DOPE_INSTRUCTION_PARTS      6  /**< Max tokens per line: 1 opcode + 5 operands */
#define DOPE_OPERAND_SIZE          10  /**< Max length of each operand string (e.g. "X", "13.5") */
#define DOPE_OPERANDS_MAX           5  /**< Max number of operands an instruction can take */
#define DOPE_INSTRUCTION_COUNT     19  /**< Total number of valid opcodes in DOPE language */

#endif
