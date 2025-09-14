#include "DOPE/dope_constants.h"
#include "DOPE/dope_program.h"

int main() {
    dope_program_t* program = dope_new_program(DOPE_PROGRAM_LINES_MAX);

    dope_input_program(program, stdin);


    dope_free_program(program);
    return 0;
}
