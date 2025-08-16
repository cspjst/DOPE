#include "DOPE/dope_sheet.h"
#include "DOPE/dope_types.h"

int main() {
    dope_program_t* program = dope_new_program();
    dope_input_program(program, stdin);
    dope_print_program(program);
    dope_free_program(program);
    return 0;
}
