#include "DOPE/dope_test_data.h"
#include "DOPE/dope_test_program.h"

int main() {
    //test_dope_lookup_opcode();
    //test_dope_input_instruction();
    //test_dope_input_program();

    test_dope_is_number();
    test_dope_parse_number();
    test_dope_parse_label();
    test_dope_input_arg();
    test_dope_input_data();

    return 0;
}
