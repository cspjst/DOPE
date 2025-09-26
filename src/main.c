#include "DOPE/dope_constants.h"
#include "DOPE/dope_program.h"
#include "DOPE/dope_data.h"
#include "DOPE/dope_interpret.h"

int main() {
    dope_program_t* program = dope_new_program(DOPE_PROGRAM_LINES_MAX);
    dope_data_t* data = dope_new_data(5);

    printf("Enter program:\n");
    dope_input_program(program, stdin);
    printf("Enter data:\n");
    dope_input_data(data, stdin);
    dope_print_program(program, stdout);
    dope_print_data(program, stdout);
    printf("Press <ENTER> to run\n");
    getchar();
    dope_interpret(15, program, data);

    dope_free_program(program);
    dope_free_data(data);
    return 0;
}
