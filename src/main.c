#include "DOPE/dope_program.h"
#include "DOPE/dope_test.h"
//#include "DOPE/dope_types.h"
//#include <stdio.h>

int main() {

    dope_program_t* prog = dope_new_program(10);

    dope_free_program(prog);

    //test_dope_is_truncated();
    //test_dope_consume_remaining_manual(stdin);
    //test_dope_read_line();
    //test_dope_instruction_tokenize();
    //test_dope_lookup_opcode();
    //test_dope_input_instruction();

    test_dope_input_program();

    return 0;
}
