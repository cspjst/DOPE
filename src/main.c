//#include "DOPE/dope_program_tape.h"
#include "DOPE/dope_test.h"
//#include "DOPE/dope_types.h"
//#include <stdio.h>

int main() {

    //dope_program_tape_t* prog = dope_new_program_tape(10);

    //dope_free_program_tape(prog);

    //test_dope_is_truncated();
    //test_dope_consume_remaining_manual(stdin);
    //test_dope_read_line();
    //test_dope_instruction_tokenize();
    //test_dope_lookup_opcode();
    //test_dope_input_instruction();

    test_dope_input_program();

    return 0;
}
