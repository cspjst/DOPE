#include "DOPE/dope_constants.h"
#include "DOPE/dope_program.h"
#include "DOPE/dope_data.h"
#include "DOPE/dope_repl.h"




int main() {
    dope_program_t* program = dope_new_program(DOPE_PROGRAM_LINES_MAX);
    dope_data_t* data = dope_new_data(5);

    dope_repl(program, data);

    dope_free_program(program);
    dope_free_data(data);
    return 0;
}
