//#include "DOPE/dope_program_tape.h"
#include "DOPE/dope_data_block.h"
#include "DOPE/dope_test.h"
//#include "DOPE/dope_types.h"
//#include <stdio.h>

int main() {

    dope_data_block_t* data = dope_new_data_block(7);

    dope_print_data_block(data);

    dope_free_data_block(data);

    //test_dope_is_truncated();
    //test_dope_consume_remaining_manual(stdin);
    //test_dope_read_line();
    //test_dope_instruction_tokenize();
    //test_dope_lookup_opcode();
    //test_dope_input_instruction();
    //test_dope_input_program();

    return 0;
}
