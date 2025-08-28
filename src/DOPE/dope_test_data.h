#include "dope_data_block.h"
#include <assert.h>

void test_dope_input_data_block() {

}


/*
fprintf(f, "SQR X Y\n");                     // valid
fprintf(f, "this_line_is_way_too_long_exceeding_DOPE_LINE_SIZE\n");  // truncated
fprintf(f, "+ A B C\n");                     // valid, 3 operands
fprintf(f, "J Z \n");                        // valid, 1 operand white space accounted for
fprintf(f, "J Z 15\n");                      // invalid, too many operands
fprintf(f, "FOO\n");                         // unknown instruction
fprintf(f, "\n");                            // empty line
fprintf(f, "E\n");                           // valid, no operands
fprintf(f, "P X\n");                         // valid, 1 operand
fprintf(f, "P\n");                           // too few args
fprintf(f, "Z X Y Z A\n");                   // too many args (Z takes 3, this is 3? check DOPE_FEILDS)
 */
