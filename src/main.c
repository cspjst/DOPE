#include "DOPE/dope_program.h"

int main() {
    dope_program_t* prog = dope_new_program(10);
    
    dope_program_free(prog);
    return 0;
}
